#pragma once
#include "RGBColor.h"

class RenderFrame
{
	public:
		RenderFrame();
		~RenderFrame();

		void setImageDimensions(int height, int width);

		int getHeight();
		int getWidth();
		RGBColor* getPixelBuf();

	private:
		int height;
		int width;
		RGBColor* pixelBuffer;
};