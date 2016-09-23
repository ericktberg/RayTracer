#pragma once
#include "Camera.h"
#include <iostream>

#include <math.h>

using namespace std;

Camera::Camera(Point3D xyz = { 0, 0, 0 }, Vector3D viewingDir = { 1, 0, 0 }, Vector3D upDir = { 0, 0, 1 }, double  dist = 1, double fov = 45) : Object(xyz), basis(upDir, viewingDir)
{
	viewDistance = dist;
	fovV = fov;
	generateViewingPlane(100, 100);
}

Camera::~Camera()
{
}

Basis3D Camera::getBasis(){	return basis; }
Plane Camera::getViewPlane(){ return viewPlane; }

void Camera::generateViewingPlane(int pixHeight, int pixWidth){
	double height = tan(fovV / 2) * 2 * viewDistance;
	double width = (pixWidth * height) / pixHeight;
	Point3D center = location + basis.w.getPointAt(viewDistance);
	cout << "Center: " << center.x << " " << center.y << " " << center.z << "\n";
	viewPlane = { center, height, width, basis };
}
