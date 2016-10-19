#pragma once
#include "Object.h"
#include "Ray3D.h"
#include "Vector3D.h"
#include "Vertex.h"

#include <vector>

namespace object{

	class Triangle : public Object
	{
	public:
		//References vertices only. Change vertices at source to modify vertex locations. 
		Triangle(const Vertex* v1, const Vertex* v2, const Vertex* v3);
		~Triangle();

		void addVertex(const Vertex* new_vertex);

		double rayCollision(const Ray3D& ray) const;
		Vector3D getNormal(const Point3D& surfacePoint) const;

	private:
		std::vector<const Vertex*> vertices_; //limit 3. Order determines normal face normal direction.
	};

}