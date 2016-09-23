/*
	** Object.h **
	Erick Berg : 9/18/2016
	Base class for all Objects represented in a scene.
	Has an orientation, location, and color.
*/

#pragma once
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "RGBColor.h"

class Object
{
	public:
		Object(double x = 0, double y = 0, double z = 0, int r = 0, int g = 0, int b = 0);
		Object(RGBColor rgb, double x = 0, double y = 0, double z = 0);
		Object(Point3D xyz, int r = 0, int g = 0, int b = 0);
		// Currently, only used constructor
		Object(Point3D xyz, RGBColor rgb);

		virtual ~Object();

		// Accessors
		Point3D getLocation();
		RGBColor getObjectColor();
		Basis3D getOrientation();

		// Mutators
		void setLocation(double x, double y, double z);
		void setObjectColor(double r, double g, double b);
		void setOrientation(Vector3D v, Vector3D w);
 
		// ::Will calculate collision of rays based on triangles in object::
		// Override in case of derived parametric object.
		virtual double rayCollision(Ray3D ray, double nearDist, RGBColor* assignColor);

	protected:

		// Object Transformation parameters
		Basis3D orientation;
		Point3D location;

		RGBColor objectColor;

	private:

};

