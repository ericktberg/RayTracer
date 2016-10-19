/*
	** Point3D.h **
	Erick Berg : 9/22/2016
	3 dimensional point abstraction
*/

#pragma once

class Point3D{
	// Defaults to 0,0,0
public:
	Point3D(double x=0, double y=0, double z=0) : x_(x), y_(y), z_(z) {};
	
	friend Point3D operator+(const Point3D p1, const Point3D p2){
		Point3D result(p1.x_ + p2.x_, p1.y_ + p2.y_, p1.z_ + p2.z_);
		return result;
	}

	friend Point3D operator-(const Point3D p1, const Point3D p2){
		Point3D result(p1.x_ - p2.x_, p1.y_ - p2.y_, p1.z_ - p2.z_);
		return result;
	}

	friend Point3D operator*(const Point3D p, const double scalar){
		Point3D result(p.x_ * scalar, p.y_ * scalar, p.z_ * scalar);
		return result;
	}

	friend Point3D operator/(const Point3D p, const double scalar){
		Point3D result(p.x_ / scalar, p.y_ / scalar, p.z_ / scalar);
		return result;
	}

	double x() const { return x_; };
	double y() const { return y_; };
	double z() const { return z_; };

protected:

	double x_;
	double y_;
	double z_;
};