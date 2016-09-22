#pragma once
#include "Camera.h"

#include <math.h>

Camera::Camera(Point3D xyz, Vector3D viewingDir, Vector3D upDir, double dist, double fov) : Object(xyz), basis(viewingDir, upDir)
{
 
}

Camera::~Camera()
{
}

void Camera::generateViewingPlane(int pixHeight, int pixWidth){
	double height = tan(fovV / 2) * 2 * viewDistance;
	double width = (pixWidth * height) / pixHeight;
	Point3D center = location + basis.w.getPointAt(viewDistance);
	viewPlane = { location, height, width, basis };
}
