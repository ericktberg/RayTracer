#pragma once
#include "Plane.h"
#include "Point3D.h"
#include "Ray3D.h"
#include "RenderEngine.h"
#include "RGBColor.h"
#include "Scene.h"

RenderEngine::RenderEngine() {}

RenderEngine::RenderEngine(int height, int width)
{
	pxImageHeight = height;
	pxImageWidth = width;
	renderImage = new RGBColor[pxImageHeight*pxImageWidth];
}


RenderEngine::~RenderEngine()
{
	delete[] renderImage;
}

void RenderEngine::setImageDimensions(int height, int width){
	pxImageHeight = height;
	pxImageWidth = width;
	renderImage = new RGBColor[pxImageHeight*pxImageWidth];
}

int RenderEngine::getHeight(){
	return pxImageHeight;
}
int RenderEngine::getWidth(){
	return pxImageWidth;
}

RGBColor* RenderEngine::render(Camera renderCamera, Scene renderScene){
	// Initialize necessary objects
	renderCamera.generateViewingPlane(pxImageHeight, pxImageWidth);
	Plane viewPlane = renderCamera.getViewPlane();
	Object** sceneObjects = renderScene.getObjects();

	// initialize background color.
	RGBColor initColor = renderScene.getBkgColor();

	// TODO? Split ray tracing implementation away from renderer?

	// Trace rays (single-threaded now for simplicity)
	// Mapping from viewPlane to image pixels
	Point3D pixel = viewPlane.ul;
	Point3D deltaH = ( viewPlane.ll - viewPlane.ul ) / (pxImageHeight - 1);
	Point3D deltaW = (viewPlane.ur - viewPlane.ul) / (pxImageWidth - 1);

	RGBColor iterColor = initColor;
	int numObjects = renderScene.getNumObjects();

	for (int i = 0; i < pxImageHeight; i++){
		for (int j = 0; j < pxImageWidth; j++){
			// Iterate pixel through viewPlane
			pixel = viewPlane.ul + deltaH*i + deltaW*j;
			
			// Calculate ray from pixel -> eye
			Point3D eye = renderCamera.getLocation();
			Vector3D rayVec(pixel, eye);
			Ray3D ray = { rayVec, eye };

			// Find minimum distance to an object and color of it
			double minDistance = -1;
			for (int k = 0; k < numObjects; k++){
				minDistance = sceneObjects[k]->rayCollision(ray, minDistance, &iterColor);
			}

			// save nearest color
			renderImage[i*pxImageWidth + j] = iterColor;
			// Reset color to background
			iterColor = initColor;
		}
	}
	return renderImage;
}