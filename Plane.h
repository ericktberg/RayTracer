#pragma once
#include "Vector3D.h"
#include "Point3D.h"

struct Plane {
	Plane(Point3D center, double height, double width, Basis3D basis) {
		ul = center + basis.u.getPointAt(-width / 2) + basis.v.getPointAt(height / 2);
		ur = center + basis.u.getPointAt(width / 2) + basis.v.getPointAt(height / 2);
		ll = center + basis.u.getPointAt(-width / 2) + basis.v.getPointAt(-height / 2);
		lr = center + basis.u.getPointAt(width / 2) + basis.v.getPointAt(-height / 2);
	};
	Plane() : ul({ -1, 0, 1 }), ur({ 1, 0, 1 }), ll({ -1, 0, -1 }), lr({ 1, 0, -1 }) {};
	Plane(Point3D ul, Point3D ur, Point3D ll, Point3D lr) : ul(ul), ur(ur), ll(ll), lr(lr) {};

	Point3D ul;
	Point3D ur;
	Point3D ll;
	Point3D lr;
};

