/*
	** Ray3D.h **
	Erick Berg : 9/22/2016
	3 dimensional ray abstraction
*/

#pragma once

#include "Vector3D.h"
#include "Point3D.h"

class Ray3D{
	public:
		Ray3D(Vector3D direction = { 0, 0, 0 }, Point3D origin = { 0, 0, 0 }) : direction_(direction), origin_(origin) {};

		Point3D origin(void) const { return origin_; };
		Vector3D direction(void) const { return direction_; };

		Point3D point_at(double t) const { return direction_.getPointAt(t) + origin_; };

	private:
		Vector3D direction_; // should be unit-length
		Point3D origin_;
};