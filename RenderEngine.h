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

#include <vector>

class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();
	
	//finds the minimum distance to an object
	int traceRay(std::vector<Object*> objects, Ray3D* ray);
	//calculates the pixel color given an object, its material, and a list of all the lights in the scene.
	RGBColor shadeRay(const Object& object, Point3D intersectionPoint, Point3D eye, std::vector<Light*> lightList, Material* objectMaterial);

	// Flagship function of program.
	// Given a camera and scene, produce an image as an array of pixels
	// Calculates viewing plane for camera from image dimensions
	RenderFrame* render(Camera renderCamera, Scene renderScene, RenderFrame* frame);

private:
	std::vector<Object*> sceneObjects;
};

