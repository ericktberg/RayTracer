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
#include "Vector3D.h"
#include "Point3D.h"

// TODO: rethink camera's implementation as an Object.
class Camera
{
	public:
		Camera();
		Camera(Point3D xyz, Vector3D viewingDir, Vector3D upDir, double dist, double fov);
		~Camera();

		Basis3D getBasis() const { return basis; };
		Plane getViewPlane() const { return viewPlane; };
		Point3D getEyeLocation() const { return eye; };
		double getViewDistance() const { return viewDistance; };
		double getFovV() const { return fovV; };

		// Create a viewing plane based on camera basis
		// Part of render process
		void generateViewingPlane(int pixHeight, int pixWidth);

		//For changing camera params. Ensure consistency by setting everything at once
		void resetParams(Point3D xyz, Vector3D viewingDir, Vector3D upDir, double dist, double fov);

	private:
		Plane viewPlane; // Viewing plane. Created on render
		Point3D eye; // eye origin
		Basis3D basis; // Definition of viewing direction and camera angle
		double viewDistance; // Distance to viewing plane
		double fovV; // Vertical Field of View in degrees

};