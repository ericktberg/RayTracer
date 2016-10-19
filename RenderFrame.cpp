#include "RenderFrame.h"


RenderFrame::RenderFrame()
{
}


RenderFrame::~RenderFrame()
{
	delete [] pixelBuffer;
}

void RenderFrame::setImageDimensions(int h, int w){
	height = h;
	width = w;
	pixelBuffer = new RGBColor[height * width];
}