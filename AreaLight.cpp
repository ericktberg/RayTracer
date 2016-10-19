#include "AreaLight.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>

namespace light{

	AreaLight::AreaLight(int x, int y, int z, int type, RGBColor hue, double radius, int sample_points) : Light(x, y, z, type, hue, sample_points), radius(radius)
{
}


AreaLight::~AreaLight()
{
}	

Point3D AreaLight::get_location() const{
	double rx = ((double) rand() / RAND_MAX) * 2 * radius - radius;
	double ry = ((double)rand() / RAND_MAX) * 2 * radius - radius;
	double rz = ((double)rand() / RAND_MAX) * 2 * radius - radius;
	Point3D rPoint = { rx, ry, rz };
	double proportion = (abs(rx) + abs(ry) + abs(rz)) / radius;
	rPoint = rPoint / proportion;
	return location + rPoint;
}

int AreaLight::casts_soft() const{
	return 1;
}
}