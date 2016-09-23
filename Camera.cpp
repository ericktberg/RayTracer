#pragma once
#include "Camera.h"

#include <math.h>

Camera::Camera(){}

Camera::Camera(Point3D xyz = { 0, 0, 0 }, Vector3D viewingDir = { 1, 0, 0 }, Vector3D upDir = { 0, 0, 1 }, double  dist = 1, double fov = 45) : Object(xyz), basis(upDir, viewingDir)
{
	viewDistance = dist;
	fovV = fov;
}

Camera::~Camera()
{
}

Basis3D Camera::getBasis(){	return basis; }
Plane Camera::getViewPlane(){ return viewPlane; }

void Camera::resetParams(Point3D xyz, Vector3D viewingDir, Vector3D upDir, double dist, double fov){
	location = xyz;
	basis = { upDir, viewingDir };
	viewDistance = dist;
	fovV = fov;
}

void Camera::generateViewingPlane(int pixHeight, int pixWidth){
	// extrapolate height from field of view and distance
	double height = tan(fovV / 2) * 2 * viewDistance;
	// width falls out of aspect ratio
	double width = (pixWidth * height) / pixHeight;

	Point3D center = location + basis.w.getPointAt(viewDistance);
	viewPlane = { center, height, width, basis };
}
