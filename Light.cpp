#include "Light.h"
#include <iostream>
namespace light{

	Light::Light(double x, double y, double z, int state, RGBColor color, int num_samples) : type(state), hue(color), num_samples_(num_samples)
{
	if (!state){
		dir = { x, y, z };
	}
	location = { x, y, z };

}


Light::~Light()
{
}

void Light::calc_samples(){
	for (int i = 0; i < num_samples_; i++){
		sample_point();
	}
}

Point3D Light::get_sample(int index) const{
	//std::cout << "sample size: " << sample_points_.size() << "index: " << index << std::endl;
	return sample_points_.at(index);
}

void Light::sample_point(){
	sample_points_.push_back(get_location());
}

int Light::casts_soft() const{
	return 0;
}

}
