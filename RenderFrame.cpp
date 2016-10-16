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

int RenderFrame::getHeight(){
	return height;
}
int RenderFrame::getWidth(){
	return width;
}
RGBColor* RenderFrame::getPixelBuf(){
	return pixelBuffer;
}
