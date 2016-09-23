#pragma once
#include "Point3D.h"
#include <math.h>


// Abstraction for 3D vectors. 
// TODO: Migrate to class
struct Vector3D {

	// Common constructor. Default <0,0,0>
	Vector3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) { normalize(); };
	// Constructs based on subtraction of points, p1 from p2.
	Vector3D(Point3D p2, Point3D p1) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) { normalize(); };

	double x;
	double y;
	double z; 
	
	//Create a new vector orthogonal to this and given vector
	Vector3D crossProduct(Vector3D v2){
		Vector3D result;
		result.x = y * v2.z - z * v2.y;
		result.y = -(x * v2.z - z * v2.x);
		result.z = x * v2.y - y * v2.x;
		result.normalize();
		return result;
	};

	double dot(Vector3D v2){
		double result = x * v2.x + y * v2.y + z * v2.z;
		return result;
	}

	void normalize(){
		double norm = sqrt(x*x + y*y + z*z);
		x = x / norm;
		y = y / norm;
		z = z / norm;
	};
	
	Point3D getPointAt(double distance){
		Point3D result = { x*distance, y*distance, z*distance };
		return result;
	}
};

struct Basis3D {
	// Default is canonical 3d basis
	Basis3D() : u({ 0, 1, 0 }), v({ 0, 0, 1 }), w({ 1, 0, 0 }) {};
	// 3D basis constructed from a 2D basis then normalized.
	
	Basis3D(Vector3D b, Vector3D c) {
		w = c;
		u = w.crossProduct(b);
		v = u.crossProduct(w);
	};

	Vector3D u;
	Vector3D v;
	Vector3D w;
};


