/*
	** Plane.h **
	Erick Berg : 9/22/2016
	Abstraction for a plane.
*/

#pragma once
#include "Vector3D.h"
#include "Point3D.h"


//TODO: Make a class that inherits from Object.
struct Plane {

	// Create a plane from a center, edge length, and a basis.
	Plane(Point3D center, double height, double width, Basis3D basis) {
		ul = center + basis.u.getPointAt(-width / 2) + basis.v.getPointAt(height / 2);
		ur = center + basis.u.getPointAt(width / 2) + basis.v.getPointAt(height / 2);
		ll = center + basis.u.getPointAt(-width / 2) + basis.v.getPointAt(-height / 2);
		lr = center + basis.u.getPointAt(width / 2) + basis.v.getPointAt(-height / 2);
	};
	// Default plane.
	Plane() : ul({ -1, 0, 1 }), ur({ 1, 0, 1 }), ll({ -1, 0, -1 }), lr({ 1, 0, -1 }) {};

	// Create plane from 4 points
	Plane(Point3D ul, Point3D ur, Point3D ll, Point3D lr) : ul(ul), ur(ur), ll(ll), lr(lr) {};

	// Four corners
	Point3D ul;
	Point3D ur;
	Point3D ll;
	Point3D lr;
};

