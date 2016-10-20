#pragma once
#include "Plane.h"
#include "Point3D.h"
#include "Ray3D.h"
#include "RenderEngine.h"
#include "RenderFrame.h"
#include "RGBColor.h"
#include "Scene.h"
#include "UVCoord.h"

#include <iostream>
#include <vector>


using std::string;

RenderEngine::RenderEngine() {}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::traceRay(const Scene& scene, const Ray3D& ray, ray::RayPayload* payload){

	// Find minimum distance to an object and color of it
	int numObjects = scene.get_num_objects();
	//std::cout << "num_objects: " << numObjects << std::endl;
	double minDistance = -1;
	int closestObj = -1;
	for (int k = 0; k < numObjects; k++){
		//std::cout << "object number: " << k << std::endl;
		const object::Object* currentObject = scene.object_at(k);
		double distance = currentObject->rayCollision(ray);

		//Test for relative distance
		int isNegative = distance < 0;
		int isNearer = (minDistance > 0 && minDistance > distance) || minDistance < 0;

		if (isNearer && !isNegative){
			//std::cout << "nearer: " << distance << std::endl;
			minDistance = distance;
			closestObj = k;
			payload->set_object_id(closestObj);
		}

	}
	payload->set_distance(minDistance);
}

RGBColor RenderEngine::shadeRay(const int objectID, const Scene& scene, const Point3D& intersectionPoint, const Point3D& eye){
	int numLights = scene.get_num_lights();
	const object::Object* object = scene.object_at(objectID);
	const Material* objectMaterial = scene.material_of(objectID);
	const PPMFile* texture;
	int texture_index = scene.texture_index_of(objectID);

	Vector3D viewDir(eye, intersectionPoint);
	viewDir.normalize();
	Vector3D surfaceNormal = object->getNormal(intersectionPoint);
	
	RGBColor result = objectMaterial->calcAmbient();
	for (int i = 0; i < numLights; i++){
		RGBColor* override_color;

		if (texture_index >= 0){
			texture = scene.texture_at(texture_index);
			object::UVCoord uvs = object->get_uv(intersectionPoint);
			override_color = &texture->get_pixel(uvs);
		}
		else{
			override_color = nullptr;
		}

		using light::Light;
		const Light* light = scene.light_at(i);

		//TODO? Currently has random behavior when object intersects area light
		double shadow = sendShadowPacket(scene, light, intersectionPoint);

		RGBColor diffSpec = { 0, 0, 0 };
		Vector3D lightDir(light->get_center(), intersectionPoint);
		lightDir.normalize();
		Vector3D h = viewDir + lightDir;
		diffSpec = diffSpec + objectMaterial->calcDiffSpec(surfaceNormal, lightDir, h, light->get_color(), shadow, override_color);
		//Add specular and diffuse onto ambient and other lights
		result = result + diffSpec;
		result.clamp();

	}
	

	return result;
}


double RenderEngine::sendShadowPacket(const Scene& scene, const light::Light* light, const Point3D& startingPoint){
	double shadow_level_inverted = 0;
	int shadow_samples = light->num_samples();
	int count = 0;
	ray::RayPayload* payload = new ray::RayPayload();
	for (int i = 0; i < shadow_samples; i++){
		Vector3D lightDir(light->get_sample(i), startingPoint);
		lightDir.normalize();
		if (light->is_directional()){
			lightDir = light->get_direction();
		}
		
		Ray3D lightRay = { lightDir, startingPoint };
		traceRay(scene, lightRay, payload);

		double distance = payload->get_load_distance();
		double distance_to_light = lightDir.length();

		if (payload->get_object_id() >= 0 && .00001 < distance && distance < distance_to_light){
			shadow_level_inverted++;
		}

		payload->reset();

		count++;
	}

	if (payload){
		delete payload;
	}
	return 1.0 - (shadow_level_inverted / count);
}


RenderFrame* RenderEngine::render(Camera* renderCamera, const Scene& renderScene, RenderFrame* frame){
	// Initialize necessary objects
	int pxImageHeight = frame->getHeight();
	int pxImageWidth = frame->getWidth();
	RGBColor* renderImage = frame->getPixelBuf();

	renderCamera->generateViewingPlane(pxImageHeight, pxImageWidth);
	Plane viewPlane = renderCamera->getViewPlane();

	// initialize background color.
	RGBColor initColor = renderScene.get_bkg_color();

	// Trace rays (single-threaded now for simplicity)
	// Mapping from viewPlane to image pixels
	Point3D pixel = viewPlane.ul;
	Point3D deltaH = ( viewPlane.ll - viewPlane.ul ) / (pxImageHeight - 1);
	Point3D deltaW = (viewPlane.ur - viewPlane.ul) / (pxImageWidth - 1);

	Point3D eye = renderCamera->getEyeLocation();
	int numObjects = renderScene.get_num_objects();
	ray::RayPayload* payload = new ray::RayPayload();

	for (int i = 0; i < pxImageHeight; i++){
		for (int j = 0; j < pxImageWidth; j++){
			// Iterate pixel through viewPlane
			pixel = viewPlane.ul + deltaH*i + deltaW*j;
			
			// Calculate ray from pixel -> eye
			Vector3D rayVec(pixel, eye);
			rayVec.normalize();
			Ray3D ray = { rayVec, eye };	
			traceRay(renderScene, ray, payload);
			int nearestObj = payload->get_object_id();
			// save nearest color
			if (nearestObj >= 0){
				renderImage[i*pxImageWidth + j] = shadeRay(nearestObj, renderScene, eye + rayVec.getPointAt(payload->get_load_distance()), eye);
			}
			else {
				renderImage[i*pxImageWidth + j] = initColor;
			}

			payload->reset();
		}
	}

	if (payload){
		delete payload;
	}
	//pixelbuffer has been altered to contain the image
	return frame;
}