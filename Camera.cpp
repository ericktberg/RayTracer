#pragma once
#include "Camera.h"

#include <iostream>
#include <math.h>

#define PI 3.14159265

Camera::Camera(){}

Camera::Camera(Point3D xyz = { 0, 0, 0 }, Vector3D viewingDir = { 1, 0, 0 }, Vector3D upDir = { 0, 0, 1 }, double  dist = 1, double fov = 45) : eye(xyz), basis(upDir, viewingDir), viewDistance(dist), fovV(fov)
{
}

Camera::~Camera()
{
}

void Camera::resetParams(Point3D xyz, Vector3D viewingDir, Vector3D upDir, double dist, double fov){
	eye = xyz;
	basis = { upDir, viewingDir };
	viewDistance = dist;
	fovV = fov;
}

void Camera::generateViewingPlane(int pixHeight, int pixWidth){
	// extrapolate height from field of view and distance
	double height = tan(fovV * PI / 360) * 2 * viewDistance;
	std::cout << height;
	// width falls out of aspect ratio
	double width = (pixWidth * height) / pixHeight;

	Point3D center = eye + basis.w.getPointAt(viewDistance);
	viewPlane = { center, height, width, basis };
}
