#include "Vector3D.h"

#include <iostream>
#include <math.h>

Vector3D::Vector3D(double a, double b, double c) : x_(a), y_(b), z_(c) { 
	normalize(); 
};

// A vector is the result of a point 2 from point 1
Vector3D::Vector3D(Point3D p2, Point3D p1) : x_(p2.x() - p1.x()), y_(p2.y() - p1.y()), z_(p2.z() - p1.z()) { };

Vector3D operator*(Vector3D v, double scalar){
	return{ v.x_*scalar, v.y_*scalar, v.z_*scalar };
}
Vector3D operator/(Vector3D v, double scalar){
	if (scalar == 0){
		std::cerr << "Vector3D operator/(Vector3D,double): SCALAR IS ZERO. DIVIDE BY ZERO BIG NO-NO\n";
		return{ 0, 0, 0 };
	}
	return{ v.x_ / scalar, v.y_ / scalar, v.z_ / scalar };
}
Vector3D operator+(Vector3D v1, Vector3D v2){
	return{ v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_ };
}

//Create a new vector orthogonal to this and given vector
Vector3D Vector3D::crossProduct(Vector3D v2) const{
	double result_x = y_ * v2.z_ - z_ * v2.y_;
	double result_y = -(x_ * v2.z_ - z_ * v2.x_);
	double result_z = x_ * v2.y_ - y_ * v2.x_;
	return { result_x, result_y, result_z };
};

// Perform inner product on this and given vector
double Vector3D::dot(Vector3D v2) const{
	double result = x_ * v2.x() + y_ * v2.y() + z_ * v2.z();
	return result;
}

int Vector3D::isParallel(Vector3D v2) const{
	Vector3D tester = this->crossProduct(v2);
	return tester.x() == 0 && tester.y() == 0 && tester.z() == 0;
}
int Vector3D::isOrthogonal(Vector3D v2){
	return this->dot(v2) == 0;
}

// Convert vector to unit length
void Vector3D::normalize(){
	double norm = sqrt(x_*x_ + y_*y_ + z_*z_);
	if (norm){
		x_ = x_ / norm;
		y_ = y_ / norm;
		z_ = z_ / norm;
	}

	//length == 0 iff this == {0,0,0}
	length_ = norm;
};

// Calculate a point at the given distance along this vector
Point3D Vector3D::getPointAt(double distance) const{
	Point3D result = { x_*distance, y_*distance, z_*distance };
	//std::cout << "point at: " << result.x() << " : " << result.y() << " : " << result.z() << std::endl; 
	return result;
}