#include "Point3D.h"

// All of the overloaded arithmetic for Point3D

Point3D operator+(const Point3D p1, const Point3D p2){
	return { p1.x + p2.x, p1.y + p2.y, p1.z + p2.z };
}

Point3D operator-(const Point3D p1, const Point3D p2){
	return { p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
}

Point3D operator*(const Point3D p, double scalar){
	return{ p.x * scalar, p.y * scalar, p.z * scalar };
}

Point3D operator/(const Point3D p, double scalar){
	return { p.x / scalar, p.y / scalar, p.z / scalar };
}