#pragma once
#include "RGBColor.h"
#include "Point3D.h"

namespace ray{

struct RayPayload{
	RayPayload() : object_idx_(-1.0), distance_to_load_(-1.0) {};
	double get_load_distance() const { return distance_to_load_; };
	int get_object_id() const { return object_idx_; };
	void set_object_id(int id) { object_idx_ = id; };
	void set_distance(double distance) { distance_to_load_ = distance; };
	void reset() {
		object_idx_ = -1.0;
		distance_to_load_ = -1.0;
	}

	int object_idx_;
	double distance_to_load_;
};

}