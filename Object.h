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
		virtual double rayCollision(Ray3D ray);

		virtual Vector3D getNormal(Point3D surfacePoint) const;

	protected:

		// Object Transformation parameters
		Basis3D orientation;
		Point3D location;

		RGBColor objectColor;

	private:

};

