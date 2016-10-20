#pragma once
#include "Object.h"
#include <iostream>

using namespace std;

namespace object{

	Object::Object(Point3D xyz, RGBColor rgb) : orientation({ 1, 0, 0 }, { 0, 0, 1 }) {
		location = xyz;
		objectColor = rgb;
	}

	Object::~Object()
	{
	}

	Vector3D Object::getNormal(const Point3D& surfacePoint) const {
		return{ 0, 0, 0 };
	}

	//TODO: add default ray collision behavior for polygonal objects
	double Object::rayCollision(const Ray3D& ray) const{
		//std::cout << "i shouldn't be here" << std::endl;
		return 1;
	}

}