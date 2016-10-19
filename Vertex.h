#pragma once
#include "Point3D.h"
#include "Vector3D.h"

namespace object{

class Vertex : public Point3D
{
public:
	Vertex(double x, double y, double z);
	Vertex(Point3D xyz);
	~Vertex();

	void set_vertex_normal(Vector3D normal ) {	vertex_normal_ = normal; };

private:
	Vector3D vertex_normal_;
};

}