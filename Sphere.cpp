#include "Sphere.h"
#include "Ray3D.h"
#include "Vector3D.h"

#include <math.h>
#include <algorithm>
#include <iostream>

#ifndef PI
#define PI 3.14159
#endif


using namespace std;

namespace object{

	Sphere::Sphere(Point3D center, double r, RGBColor c) : Object(center, c)
	{
		radius = r;
		centerPoint = center;
	}


	Sphere::~Sphere()
	{
	}

	Vector3D Sphere::getNormal(const Point3D& surfacePoint) const{
		Vector3D normal(surfacePoint, location);
		return normal / radius;
	}

	UVCoord Sphere::get_uv(const Point3D& intersection) const{
		Vector3D normal = getNormal(intersection);
		double phi = acos(-normal.z());
		double theta = atan2(normal.y(), normal.x());
		double v = phi / PI;
		double u = (theta + PI) / (2 * PI);
		//std::cerr << "I'm calculating sphere uvs: " << u << " : " << v <<  std::endl;
		return { u, v };
	}

	double Sphere::rayCollision(const Ray3D& ray) const{
		// at^2 + bt + c = 0
		double t;

		// A = 1 when vectors are normalized
		double a = 1;
		// B = 2 * (Xd * (Xo-Xc) + Yd * (Yo-Yc) + Zd * (Zo-Zc))
		double b = 2 * (ray.direction().x() * (ray.origin().x() - centerPoint.x())
			+ ray.direction().y() * (ray.origin().y() - centerPoint.y())
			+ ray.direction().z() * (ray.origin().z() - centerPoint.z()));

		// C = (Xo-Xc)^2 + (Yo-Yc)^2 + (Zo-Zc)^2 - r^2
		double c = (ray.origin().x() - centerPoint.x())*(ray.origin().x() - centerPoint.x())
			+ (ray.origin().y() - centerPoint.y())*(ray.origin().y() - centerPoint.y())
			+ (ray.origin().z() - centerPoint.z())*(ray.origin().z() - centerPoint.z())
			- radius*radius;

		// Quadratic formula
		double discriminant = b*b - 4 * a*c;

		//miss
		if (discriminant < 0){
			return -1;
		}
		//graze
		else if (discriminant == 0) {
			t = -b / 2;
		}
		//pierce
		else {
			t = min((-b + sqrt(discriminant)) / 2, (-b - sqrt(discriminant)) / 2);
		}
		//std::cout << "sphere t: " << t << std::endl;
		return t;
	}

}