#pragma once
#include "Plane.h"
#include "Point3D.h"
#include "Ray3D.h"
#include "RenderEngine.h"
#include "RenderFrame.h"
#include "RGBColor.h"
#include "Scene.h"

#include <vector>


using namespace std;

RenderEngine::RenderEngine() {}

RenderEngine::~RenderEngine()
{
}

int RenderEngine::traceRay(vector<Object*> objects, Ray3D* ray){
	// Find minimum distance to an object and color of it
	int numObjects = objects.size();
	double minDistance = -1;
	int closestObj = -1;
	for (int k = 0; k < numObjects; k++){
		double distance = objects[k]->rayCollision(*ray);

		//Test for relative distance
		int isNegative = distance < 0;
		int isNearer = (minDistance > 0 && minDistance > distance) || minDistance < 0;

		if (isNearer && !isNegative){
			minDistance = distance;
			closestObj = k;
		}
	}
	//ray starts unitLength, after multiplication it has unit length, but stores length as distance to intersection point
	// ray.direction.getPointAt(ray.direction.length) is intersection point
	//TODO: Make this not such a shitty design
	ray->direction = ray->direction*minDistance;
	return closestObj;
}

RGBColor RenderEngine::shadeRay(const Object& object, const Point3D& intersectionPoint, const Point3D& eye, vector<Light*> lightList, const Material& objectMaterial){
	int numLights = lightList.size();

	Vector3D viewDir(eye, intersectionPoint);
	Vector3D surfaceNormal = object.getNormal(intersectionPoint);
	
	RGBColor result = objectMaterial.calcAmbient();

	for (int i = 0; i < lightList.size(); i++){
		// ** TODO: Rethink distances and rays and vectors blahblahblah **

		//Calculate light information and vectors
		Light* light = lightList[i];
		Vector3D lightDir(light->get_location(), intersectionPoint);
		if (light->is_directional()){
			lightDir = light->get_direction();
		}
		Vector3D h = viewDir + lightDir;

		//Calculate Shadows for each light
		double shadow = 1;
		double distanceToLight = lightDir.length;
		Ray3D lightRay = { lightDir, intersectionPoint };
		if ((traceRay(sceneObjects, &lightRay) >= 0) && lightRay.direction.length < distanceToLight && lightRay.direction.length > .00001){
			shadow = 0;
		}

		//Add specular and diffuse onto ambient and other lights
		result = result + objectMaterial.calcDiffSpec(surfaceNormal, lightDir, h, light->get_color(), shadow);
		result.clamp();
	}

	return result;
}


RenderFrame* RenderEngine::render(const Camera& renderCamera, const Scene& renderScene, RenderFrame* frame){
	// Initialize necessary objects
	int pxImageHeight = frame->getHeight();
	int pxImageWidth = frame->getWidth();
	RGBColor* renderImage = frame->getPixelBuf();

	renderCamera.generateViewingPlane(pxImageHeight, pxImageWidth);
	Plane viewPlane = renderCamera.getViewPlane();
	sceneObjects = renderScene.getObjects();
	vector<Light*> sceneLights = renderScene.getLights();

	// initialize background color.
	RGBColor initColor = renderScene.getBkgColor();
	// TODO? Split ray tracing implementation away from renderer?

	// Trace rays (single-threaded now for simplicity)
	// Mapping from viewPlane to image pixels
	Point3D pixel = viewPlane.ul;
	Point3D deltaH = ( viewPlane.ll - viewPlane.ul ) / (pxImageHeight - 1);
	Point3D deltaW = (viewPlane.ur - viewPlane.ul) / (pxImageWidth - 1);

	Point3D eye = renderCamera.getEyeLocation();

	int numObjects = sceneObjects.size();

	for (int i = 0; i < pxImageHeight; i++){
		for (int j = 0; j < pxImageWidth; j++){
			// Iterate pixel through viewPlane
			pixel = viewPlane.ul + deltaH*i + deltaW*j;
			
			// Calculate ray from pixel -> eye
			Vector3D rayVec(pixel, eye);
			Ray3D ray = { rayVec, eye };
			int nearestObj = traceRay(sceneObjects, &ray);
			
			// save nearest color
			if (nearestObj >= 0){
				Material* objMaterial = renderScene.materialOf(nearestObj);
				renderImage[i*pxImageWidth + j] = shadeRay(*sceneObjects[nearestObj], eye + ray.direction.getPointAt(ray.direction.length), eye, sceneLights, objMaterial);
			}
			else {
				renderImage[i*pxImageWidth + j] = initColor;
			}
		}
	}
	//pixelbuffer has been altered to contain the image
	return frame;
}