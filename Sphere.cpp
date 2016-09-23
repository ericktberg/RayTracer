#include "Sphere.h"
#include "Ray3D.h"
#include "Vector3D.h"

#include <math.h>
#include <algorithm>

using namespace std;

Sphere::Sphere(Point3D center, double r, RGBColor c) : Object(center, c)
{
	radius = r;
	centerPoint = center;
}


Sphere::~Sphere()
{
}

double Sphere::rayCollision(Ray3D ray, double nearDist, RGBColor* assignColor){
	// at^2 + bt + c = 0
	double t;
	
	// A = 1 when vectors are normalized
	double a = 1;
	// B = 2 * (Xd * (Xo-Xc) + Yd * (Yo-Yc) + Zd * (Zo-Zc))
	double b = 2 * (  ray.direction.x * (ray.origin.x - centerPoint.x)
					+ ray.direction.y * (ray.origin.y - centerPoint.y)
					+ ray.direction.z * (ray.origin.z - centerPoint.z));

	// C = (Xo-Xc)^2 + (Yo-Yc)^2 + (Zo-Zc)^2 - r^2
	double c =    (ray.origin.x - centerPoint.x)*(ray.origin.x - centerPoint.x)
				+ (ray.origin.y - centerPoint.y)*(ray.origin.y - centerPoint.y)
				+ (ray.origin.z - centerPoint.z)*(ray.origin.z - centerPoint.z)
				- radius*radius;

	// Quadratic formula
	double discriminant = b*b - 4*a*c;

	//miss
	if (discriminant < 0){
		return -1;
	}
	//graze
	else if (discriminant = 0) {
		t = -b / 2;
	}
	//pierce
	else {
		t = min( (-b + sqrt(discriminant)) / 2, (-b - sqrt(discriminant)) / 2);
	}

	//not closer than other objects
	if (nearDist > 0 && nearDist < t){
		return nearDist;
	}

	assignColor->setColor(objectColor);

	return t;
}