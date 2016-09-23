/*
	** Ray3D.h **
	Erick Berg : 9/22/2016
	3 dimensional ray abstraction
	TODO: necessary?
*/

#pragma once

struct Ray3D{
	Vector3D direction; // should be unit-length
	Point3D origin;
};