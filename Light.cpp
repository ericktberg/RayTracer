#include "Light.h"

namespace light{

Light::Light(double x, double y, double z, int state, RGBColor color) : type(state), hue(color)
{
	if (!state){
		dir = { x, y, z };
	}
	location = { x, y, z };
}


Light::~Light()
{
}

Point3D Light::sample_point(int index){
	if (sample_points_.size() < index){
		sample_points_.push_back(get_location());
	}
	return sample_points_.at(index);
}

int Light::casts_soft() const{
	return 0;
}

}
