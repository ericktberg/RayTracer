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
		
		Object(Point3D xyz, RGBColor rgb = { 0, 0, 0 });

		virtual ~Object();

		// Accessors
		Point3D getLocation() const { return location; };
		RGBColor getObjectColor() const { return objectColor; };
		Basis3D getOrientation() const { return orientation; };

		// Mutators
		void setLocation(double x, double y, double z) { location = { x, y, z, }; };
		void setObjectColor(double r, double g, double b) { objectColor = { r, g, b }; };
		void setOrientation(Vector3D v, Vector3D w) { orientation = { v, w }; };
 
		// ::Will calculate collision of rays based on triangles in object::
		// Override in case of derived parametric object.
		virtual double rayCollision(const Ray3D& ray) const;

		virtual Vector3D getNormal(const Point3D& surfacePoint) const;

	protected:

		// Object Transformation parameters
		Basis3D orientation;
		Point3D location;

		RGBColor objectColor;

	private:

};

