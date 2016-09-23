#pragma once
#include "Object.h"

using namespace std;
Object::Object(double x, double y, double z, int r, int g, int b) : location(x, y, z), orientation()
{
	setObjectColor(r, g, b);
}

Object::Object(Point3D xyz, int r, int g, int b) : objectColor(r, g, b), orientation()
{
	location = xyz;
}

Object::Object(RGBColor rgb, double x, double y, double z) : location(x, y, z), orientation()
{
	objectColor = rgb;
}

Object::Object(Point3D xyz, RGBColor rgb) : orientation({ 1, 0, 0 }, { 0, 0, 1 }) {
	location = xyz;
	objectColor = rgb;
}

// TODO: do I need these Overloaded constructors?

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

//TODO: add default ray collision behavior for polygonal objects
double Object::rayCollision(Ray3D ray, double nearDist, RGBColor* color){
	return 1;
}