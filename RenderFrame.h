#pragma once
#include "RGBColor.h"

class RenderFrame
{
	public:
		RenderFrame();
		~RenderFrame();

		void setImageDimensions(int height, int width);

		int getHeight() const { return height; };
		int getWidth() const { return width; };
		RGBColor* getPixelBuf() const { return pixelBuffer; };

	private:
		int height;
		int width;
		RGBColor* pixelBuffer;
};