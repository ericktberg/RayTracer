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
		Object(Point3D xyz, RGBColor rgb);

		virtual ~Object();

		Point3D getLocation();
		RGBColor getObjectColor();
		Basis3D getOrientation();

		void setLocation(double x, double y, double z);
		void setObjectColor(int r, int g, int b);
		void setOrientation(Vector3D v, Vector3D w);

		// Returns point of collision. 
		virtual void testObject();
		virtual double rayCollision(Ray3D ray, double nearDist, RGBColor* assignColor);

	protected:

		Basis3D orientation;
		Point3D location;
		RGBColor objectColor;

	private:

};

