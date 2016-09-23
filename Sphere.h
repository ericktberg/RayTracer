#pragma once
#include "Object.h"
#include "Point3D.h"
#include "Ray3D.h"
#include "RGBColor.h"
#include <iostream>

using namespace std;

class Sphere : public Object
{
	public:
		Sphere(Point3D centerPoint, double r, RGBColor c);
		~Sphere();

		void testObject();
		double rayCollision(Ray3D ray, double nearDist, RGBColor* assignColor);

	private:
		double radius;
		Point3D centerPoint;
};

