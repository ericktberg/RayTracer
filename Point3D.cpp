#include "Point3D.h"

Point3D operator+(const Point3D p1, const Point3D p2){
	return { p1.x + p2.x, p1.y + p2.y, p1.z + p2.z };
}

Point3D operator-(const Point3D p1, const Point3D p2){
	return{ p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
}