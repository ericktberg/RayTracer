#pragma once
#include "Camera.h"
#include "Scene.h"

class RenderEngine
{
public:
	RenderEngine(int pxImageHeight, int pxImageWidth);
	~RenderEngine();

	RGBColor* render(Camera renderCamera, Scene renderScene);

private:
	int pxImageHeight;
	int pxImageWidth;
	RGBColor* renderImage;
};

