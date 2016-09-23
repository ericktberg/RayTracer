#pragma once
#include "Plane.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "Point3D.h"
#include "RGBColor.h"
#include "Ray3D.h"

#include <iostream>



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

RGBColor* RenderEngine::render(Camera renderCamera, Scene renderScene){
	renderCamera.generateViewingPlane(pxImageHeight, pxImageWidth);
	Plane viewPlane = renderCamera.getViewPlane();

	// initialize background color.
	RGBColor initColor = renderScene.getBkgColor();
	for (int i = 0; i < pxImageHeight * pxImageWidth; i++){
		renderImage[i] = initColor;
	}

	// trace rays (single-threaded now for simplicity)
	Point3D pixel = viewPlane.ul;
	Point3D deltaH = ( viewPlane.ll - viewPlane.ul ) / (pxImageHeight - 1);
	Point3D deltaW = (viewPlane.ur - viewPlane.ul) / (pxImageWidth - 1);
	RGBColor iterColor = initColor;
	int numObjects = renderScene.getNumObjects();
	for (int i = 0; i < pxImageHeight; i++){
		for (int j = 0; j < pxImageWidth; j++){
			pixel = viewPlane.ul + deltaH*i + deltaW*j;
			Point3D eye = renderCamera.getLocation();
			Vector3D rayVec(pixel, eye);
			Ray3D ray = { rayVec, eye };
			double minDistance = -1;
			for (int k = 0; k < numObjects; k++){
				minDistance = renderScene.objects[0]->rayCollision(ray, minDistance, &iterColor);
			}

			renderImage[i*pxImageHeight + j] = iterColor;
			iterColor = initColor;
		}
	}
	return renderImage;
}