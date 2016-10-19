#pragma once

#include "Light.h"
#include "Point3D.h"
#include "Sphere.h"

namespace light{

class AreaLight : public Light
{
public:
	AreaLight(int x, int y, int z, int type, RGBColor hue, double radius);
	~AreaLight();
	
	Point3D sample_point(int index);

	int casts_soft() const;
	Point3D get_location() const;
private:
	double radius;
};

}