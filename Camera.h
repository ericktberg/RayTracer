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
		Camera(Point3D xyz, Vector3D viewingDir, Vector3D upDir, double dist, double fov);
		~Camera();

		Basis3D getBasis();
		Plane getViewPlane();
		double getViewDistance();
		double getFovV();

		// Part of render process
		void generateViewingPlane(int pixHeight, int pixWidth);

	private:
		Plane viewPlane;
		Basis3D basis;
		double viewDistance; // Distance to viewing plane
		double fovV; // Vertical Field of View in degrees

};