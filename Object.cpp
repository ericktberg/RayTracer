#pragma once
#include "Object.h"
#include <iostream>

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

// Overloaded constructors?

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

void Object::setObjectColor(int r, int g, int b){
	objectColor = { r, g, b };
}

void Object::testObject(){
	cout << "I am an Object\n";
}

double Object::rayCollision(Ray3D ray, double nearDist, RGBColor* color){
	cout << "I am an Object\n";
	return 1;
}