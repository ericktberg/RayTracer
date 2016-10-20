/*
	** Vector.h **
	Erick Berg : 9/22/2016
	3 dimensional vector abstraction
*/

#pragma once
#include "Point3D.h"


// Abstraction for 3D vectors. 
class Vector3D {
	public:
		//Multiply a vector by a scalar
		friend Vector3D operator*(Vector3D vector, double scalar);
		//Divide a vector by a scalar
		friend Vector3D operator/(Vector3D vector, double scalar);
		//Average two vectors together (produces unit-length output)
		friend Vector3D operator+(Vector3D vector1, Vector3D vector2);


		// Common constructor. Default <0,0,0>
		Vector3D(double a = 0, double b = 0, double c = 0);

		// A vector is the result of a subtracting point 1 from point 2
		Vector3D(Point3D point2, Point3D point1);

		//Create a new vector orthogonal to this and given vector
		Vector3D crossProduct(Vector3D vector2) const;

		// Perform inner product on this and given vector
		double dot(Vector3D vector2) const;

		int isParallel(Vector3D vector2) const;
		int isOrthogonal(Vector3D vector2);

		// Convert vector to unit length
		void normalize();
	
		// Calculate a point at the given distance along this vector
		Point3D getPointAt(double distance) const;

		double x() const { return x_; };
		double y() const { return y_; };
		double z() const { return z_; };
		double length() const { return length_; };
		void x(double x) { x_ = x; };
		void y(double y) { y_ = y; };
		void z(double z) { z_ = z; };

	private:
		double x_;
		double y_;
		double z_;
		double length_;
};


// Extension of vector, abstraction of a 3 dimensional vector basis. 
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