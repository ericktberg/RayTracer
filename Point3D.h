/*
	** Point3D.h **
	Erick Berg : 9/22/2016
	3 dimensional point abstraction
*/

#pragma once

struct Point3D{
	// Defaults to 0,0,0
	Point3D() : x(0), y(0), z(0) {};
	Point3D(double a, double b, double c) : x(a), y(b), z(c) {};
	
	double x;
	double y;
	double z;
};

// Override arithmetic operators for more intuitive use
Point3D operator+(Point3D p1, Point3D p2);
Point3D operator-(Point3D p1, Point3D p2);
Point3D operator*(Point3D p, double scalar);
Point3D operator/(Point3D p, double scalar);