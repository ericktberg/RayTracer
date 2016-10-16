#pragma once
#include "Object.h"
#include "RGBColor.h"
class Light
{
public:
	Light(double x, double y, double z, int, RGBColor);
	~Light();

	Point3D get_location(){ return location; };
	RGBColor get_color(){ return hue; };
	int is_directional(){ return type; };
	Vector3D get_direction(){ return dir; };
private:
	RGBColor hue;
	Vector3D dir;
	Point3D location;
	int type;
};

