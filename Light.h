#pragma once
#include "Object.h"
#include "Point3D.h"
#include "RGBColor.h"
#include <vector>

namespace light{

class Light
{
public:
	Light(double x, double y, double z, int type, RGBColor rgb, int num_samples = 1);
	~Light();

	//Relies on proper coding to avoid out-of-bounds errors.
	//Use light::Light::num_samples() to index properly.
	Point3D get_sample(int index) const;
	int num_samples() const { return num_samples_; };

	void calc_samples();

	virtual int casts_soft() const;
	Point3D get_center() const { return location; };
	RGBColor get_color() const { return hue; };
	int is_directional() const { return !type; };
	Vector3D get_direction() const { return dir; };
protected:
	//Samples a point and add it to sample_points_
	virtual void sample_point();
	//Point as sampled from definition of light
	virtual Point3D get_location() const { return location; };

	std::vector<Point3D> sample_points_;
	int num_samples_;
	RGBColor hue;
	Vector3D dir;
	Point3D location;
	int type;
};

}