#include "Vector3D.h"

#include <iostream>
#include <math.h>

Vector3D::Vector3D(double a, double b, double c) : x(a), y(b), z(c) { normalize(); };

// A vector is the result of a point 2 from point 1
Vector3D::Vector3D(Point3D p2, Point3D p1) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) { normalize(); };

Vector3D operator*(Vector3D v, double scalar){
	return	{ v.x*scalar, v.y*scalar, v.z*scalar };
}
Vector3D operator/(Vector3D v, double scalar){
	if (scalar == 0){
		std::cerr << "Vector3D operator/(Vector3D,double): SCALAR IS ZERO. DIVIDE BY ZERO BIG NO-NO\n";
		return{ 0, 0, 0 };
	}
	return{ v.x/scalar, v.y/scalar, v.z/scalar };
}
Vector3D operator+(Vector3D v1, Vector3D v2){
	return{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

//Create a new vector orthogonal to this and given vector
Vector3D Vector3D::crossProduct(Vector3D v2){
	Vector3D result;
	result.x = y * v2.z - z * v2.y;
	result.y = -(x * v2.z - z * v2.x);
	result.z = x * v2.y - y * v2.x;
	result.normalize();
	return result;
};

// Perform inner product on this and given vector
double Vector3D::dot(Vector3D v2){
	double result = x * v2.x + y * v2.y + z * v2.z;
	return result;
}

int Vector3D::isParallel(Vector3D v2){
	Vector3D tester = this->crossProduct(v2);
	std::cout << tester.x << " " << tester.y << " " << tester.z << "\n";
	return tester.x == 0 && tester.y == 0 && tester.z == 0;
}
int Vector3D::isOrthogonal(Vector3D v2){
	return this->dot(v2) == 0;
}

// Convert vector to unit length
void Vector3D::normalize(){
	double norm = sqrt(x*x + y*y + z*z);
	if (norm){
		x = x / norm;
		y = y / norm;
		z = z / norm;
	}
	length = norm;
};

// Calculate a point at the given distance along this vector
Point3D Vector3D::getPointAt(double distance){
	Point3D result = { x*distance, y*distance, z*distance };
	return result;
}