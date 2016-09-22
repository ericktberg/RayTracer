/*
	** Camera.h **
	Erick Berg : 9/18/2016
	The basic camera object.
	Eye location is camera origin.
	Default settings:	(x,y,z) = (0,0,0); viewingDir = <1,0,0>; u = <0,1,0>, v = <0,0,1>, w= <-1,0,0>; 
						dist [distance to viewing plane] = 1; fovV = 45 degrees;
*/

#pragma once
#include "Object.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Vector3D.h"
#include "Point3D.h"

class Camera : public Object
{
	public:
		Camera(Point3D xyz = { 0, 0, 0 }, Vector3D viewingDir = { 1, 0, 0 }, Vector3D upDir = { 0, 0, 1 }, double dist = 1, double fov = 45);
		~Camera();

	private:
		Basis3D basis;
		Plane viewPlane;
		double viewDistance; // Distance to viewing plane
		double fovV; // Vertical Field of View in degrees

		void generateViewingPlane(int pixHeight, int pixWidth);
};