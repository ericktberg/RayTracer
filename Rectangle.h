#pragma once
#include "Object.h"
#include "Vector3D.h"

class Rectangle : Object
{
public:
	Rectangle();
	~Rectangle();

private:
	//basis vectors
	Vector3D u, v;
	double height, width;
};

