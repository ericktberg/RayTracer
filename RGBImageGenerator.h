/*	
	** RGBImageGenerator.h **
	Erick Berg : 9/16/2016
	An image generator. Image generation algorithms use inputs and image metaData
*/

#pragma once
#include "ImageFile.h"
#include "RGBColor.h"
#include <string>

class RGBImageGenerator
{
	public:
		RGBImageGenerator(int width, int height, int maxVal);
		~RGBImageGenerator();

		RGBColor* generateSolid(RGBColor rgb);
		RGBColor* generateGradient(RGBColor topColor, RGBColor bottomColor);

	private:
		int width;
		int height;
		int maxVal;
};

