#include "Light.h"


Light::Light(double x, double y, double z, int state, RGBColor color) : type(state), hue(color)
{
	if (!state){
		dir = { x, y, z };
	}
	location = { x, y, z };
}


Light::~Light()
{
}