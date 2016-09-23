/*
	** RenderEngine.h **
	Erick Berg : 9/22/2016
	Render Engine Main class
	
	TODO: consider associating a scene with a render engine or vis versa.
*/
#pragma once
#include "Camera.h"
#include "Scene.h"

class RenderEngine
{
public:
	RenderEngine();
	RenderEngine(int pxImageHeight, int pxImageWidth);
	~RenderEngine();

	//Accessors
	int getHeight();
	int getWidth();


	// Flagship function of program.
	// Given a camera and scene, produce an image as an array of pixels
	// Calculates viewing plane for camera from image dimensions
	RGBColor* render(Camera renderCamera, Scene renderScene);

	// Set the image dimensions
	void setImageDimensions(int height, int width);

private:
	// Image description
	int pxImageHeight;
	int pxImageWidth;
	RGBColor* renderImage;
};

