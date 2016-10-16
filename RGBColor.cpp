#include "RGBColor.h"

RGBColor operator*(RGBColor rgb, double scalar){
	double r = rgb.r * scalar;
	double g = rgb.g * scalar;	
	double b = rgb.b * scalar;	
	RGBColor result = { r, g, b };
	result.clamp();
	return result;
}

RGBColor operator+(RGBColor rgb1, RGBColor rgb2){
	double r = rgb1.r + rgb2.r;
	double g = rgb1.g + rgb2.g;
	double b = rgb1.b + rgb2.b;
	RGBColor result = { r, g, b };
	result.clamp();
	return result;
}