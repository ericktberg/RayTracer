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
		// Returns -1 on miss. Otherwise returns minimum ray distance to object
		double rayCollision(const Ray3D& ray) const;

		Vector3D getNormal(const Point3D& surfacePoint) const;

	private:
		// Parametric definition parameters
		double radius;
		Point3D centerPoint;
};

