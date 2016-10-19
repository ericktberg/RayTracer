#include "Vertex.h"

namespace object{

	Vertex::Vertex(double x, double y, double z) : Point3D(x,y,z)
	{
	}

	Vertex::Vertex(Point3D xyz) : Point3D(xyz) {

	}

	Vertex::~Vertex()
	{
	}

}