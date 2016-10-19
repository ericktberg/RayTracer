#pragma once
#include "Object.h"
#include "Point3D.h"
#include "RGBColor.h"
#include <vector>

namespace light{

class Light
{
public:
	Light(double x, double y, double z, int type, RGBColor rgb);
	~Light();

	virtual Point3D sample_point(int index);

	virtual int casts_soft() const;
	virtual Point3D get_location() const{ return location; };
	Point3D get_center() const { return location; };
	RGBColor get_color() const { return hue; };
	int is_directional() const { return !type; };
	Vector3D get_direction() const { return dir; };
protected:
	std::vector<Point3D> sample_points_;
	int num_points_;
	RGBColor hue;
	Vector3D dir;
	Point3D location;
	int type;
};

}