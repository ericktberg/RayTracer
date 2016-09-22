#pragma once

struct Point3D{
	Point3D() : x(0), y(0), z(0) {};
	Point3D(double a, double b, double c) : x(a), y(b), z(c) {};
	
	double x;
	double y;
	double z;
};

Point3D operator+(Point3D p1, Point3D p2);
Point3D operator-(Point3D p1, Point3D p2);