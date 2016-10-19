#pragma once

#include "Light.h"
#include "Point3D.h"
#include "Sphere.h"

namespace light{

class AreaLight : public Light
{
public:
	AreaLight(int x, int y, int z, int type, RGBColor hue, double radius, int num_samples = 32);
	~AreaLight();
	

	int casts_soft() const;
private:

	//Samples Point from random point cloud within radius
	Point3D get_location() const;

	double radius;
};

}