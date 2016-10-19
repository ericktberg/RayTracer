#pragma once
#include "Object.h"

using namespace std;

Object::Object(Point3D xyz, RGBColor rgb) : orientation({ 1, 0, 0 }, { 0, 0, 1 }) {
	location = xyz;
	objectColor = rgb;
}

Object::~Object()
{
}

Vector3D Object::getNormal(const Point3D& surfacePoint) const {
	return { 0, 0, 0 };
}

//TODO: add default ray collision behavior for polygonal objects
double Object::rayCollision(const Ray3D& ray) const{
	return 1;
}