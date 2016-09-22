/*	
	** RGBColor.h **
	Erick Berg : 9/16/2016
	Structs containing RGB implementations
*/

#pragma once

struct RGBColor{
	RGBColor() : r(0), g(0), b(0) {};
	RGBColor(int a, int b, int c) : r(a), g(b), b(c) {};

	int r;
	int g;
	int b;

	void clamp(){
		r = r > 255 ? 255 : (r < 0 ? 0 : r);
		g = g > 255 ? 255 : (g < 0 ? 0 : g);
		b = b > 255 ? 255 : (b < 0 ? 0 : b);
	}
};