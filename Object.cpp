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

Point3D Object::getLocation(){
	return location;
}

RGBColor Object::getObjectColor(){
	return objectColor;
}

Basis3D Object::getOrientation(){
	return orientation;
}

void Object::setLocation(double x, double y, double z){
	location = { x, y, z };
}

void Object::setObjectColor(double r, double g, double b){
	objectColor = { r, g, b };
}

Vector3D Object::getNormal(Point3D surfacePoint) const {
	return { 0, 0, 0 };
}

//TODO: add default ray collision behavior for polygonal objects
double Object::rayCollision(Ray3D ray){
	return 1;
}