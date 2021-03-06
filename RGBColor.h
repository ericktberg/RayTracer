/*	
	** RGBColor.h **
	Erick Berg : 9/16/2016
	Structs containing RGB implementations
*/

#pragma once

// TODO: Restructure to 1.0 scale. Image format saving will convert to proper scale
struct RGBColor{
	RGBColor() : r(0), g(0), b(0) {};
	RGBColor(double a, double b, double c) : r(a), g(b), b(c) {};

	double r;
	double g;
	double b;


	int rConvert(int maxVal){
		return (int)(maxVal*r);
	}
	int gConvert(int maxVal){
		return (int)(maxVal*g);
	}
	int bConvert(int maxVal){
		int resultB = (int)maxVal*b;
		return resultB;
	}

	// Sets a new color
	void setColor(RGBColor newColor){
		r = newColor.r;
		g = newColor.g;
		b = newColor.b;
	}

	// Clamps to maximum values
	void clamp(){
		r = r > 1.0 ? 1.0 : (r < 0 ? 0 : r);
		g = g > 1.0 ? 1.0 : (g < 0 ? 0 : g);
		b = b > 1.0 ? 1.0 : (b < 0 ? 0 : b);
	}

	friend RGBColor operator/(RGBColor rgb, int scalar){
		double r = rgb.r / scalar;
		double g = rgb.g / scalar;
		double b = rgb.b / scalar;
		RGBColor result = { r, g, b };
		result.clamp();
		return result;
	}


	friend RGBColor operator*(RGBColor rgb, double scalar){
		double r = rgb.r * scalar;
		double g = rgb.g * scalar;
		double b = rgb.b * scalar;
		RGBColor result = { r, g, b };
		result.clamp();
		return result;
	}

	friend RGBColor operator+(RGBColor rgb1, RGBColor rgb2){
		double r = rgb1.r + rgb2.r;
		double g = rgb1.g + rgb2.g;
		double b = rgb1.b + rgb2.b;
		RGBColor result = { r, g, b };
		result.clamp();
		return result;
	}
};