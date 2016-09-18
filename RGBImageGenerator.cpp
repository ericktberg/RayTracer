#include "RGBImageGenerator.h"


RGBImageGenerator::RGBImageGenerator(int w, int h, int maxV)
{
	width = w;
	height = h;
	maxVal = maxV;
}


RGBImageGenerator::~RGBImageGenerator()
{
}

RGBColor* RGBImageGenerator::generateSolid(RGBColor rgb){
	// DRUNK COMMENT: Must be availabilitized to avoid error "cannot use constant expression" 
	RGBColor* image;
	image = new RGBColor[height * width];

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			image[i * j] = rgb;
		}
	}
	return image;
}

RGBColor* RGBImageGenerator::generateGradient(RGBColor topColor, RGBColor bottomColor){
	RGBColor* image;
	image = new RGBColor[height * width];

	//linear gradient coefficients
	double rStep = ((double)bottomColor.r - (double)topColor.r) / (height - 1);
	double gStep = ((double)bottomColor.g - (double)topColor.g) / (height - 1);
	double bStep = ((double)bottomColor.b - (double)topColor.b) / (height - 1);

	RGBColor stepColor = topColor;

	for (int i = 0; i < height; i++){
		// Iter variables keep track of fractions
		double rIter = topColor.r + rStep*i;
		double gIter = topColor.g + gStep*i;
		double bIter = topColor.b + bStep*i;

		stepColor.r = (int)(rIter);
		stepColor.g = (int)(gIter);
		stepColor.b = (int)(bIter);

		for (int j = 0; j < width; j++){
			image[i * width +  j] = stepColor;
		}
	}

	return image;
}