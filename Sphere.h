/*
	** Sphere.h **
	Erick Berg : 9/22/2016
	Abstraction for a parametric Sphere object.
	Inherits from Object. 
	Defined by centerPoint and radius.
*/

#pragma once
#include "Object.h"
#include "Point3D.h"
#include "Ray3D.h"
#include "RGBColor.h"

class Sphere : public Object
{
	public:
		Sphere(Point3D centerPoint, double r, RGBColor c);
		~Sphere();

		// Override of Object rayCollision. 
		// Returns -1 on miss. Otherwise returns minimum of [ray intersection with object] and [nearDist]
		// TODO: Reevaluate necessity of nearDist in rayTracing implementation.
		double rayCollision(Ray3D ray, double nearDist, RGBColor* assignColor);

	private:
		// Parametric definition parameters
		double radius;
		Point3D centerPoint;
};

