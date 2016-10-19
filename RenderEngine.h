/*
	** RenderEngine.h **
	Erick Berg : 9/22/2016
	Render Engine Main class
	
*/
#pragma once
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Point3D.h"
#include "Scene.h"
#include "Ray3D.h"
#include "RenderFrame.h"
#include "RayPayload.h"

#include <vector>

class RenderEngine
{
public:
	RenderEngine();
	RenderEngine(double shadow_samples);
	~RenderEngine();
	
	// Flagship function of program.
	// Given a camera and scene, produce an image as an array of pixels
	// Calculates viewing plane for camera from image dimensions
	RenderFrame* render(Camera* renderCamera, const Scene& renderScene, RenderFrame* frame);

private:
	//finds the minimum distance to an object
	void traceRay(const Scene& scene, const Ray3D& ray, ray::RayPayload* payload);
	//calculates the pixel color given an object, its material, and a list of all the lights in the scene.
	RGBColor shadeRay(const int objectID, const Scene& scene, const Point3D& intersectionPoint, const Point3D& eye);
	double sendShadowPacket(const Scene& scene, light::Light* light, const Point3D& startingPoint);

	int shadow_samples_;
};

