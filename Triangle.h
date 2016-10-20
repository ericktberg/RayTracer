#pragma once
#include "Object.h"
#include "Ray3D.h"
#include "UVCoord.h"
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
		void add_uv_coords(UVCoord uv1, UVCoord uv2, UVCoord uv3);
		void add_vertex_normals(Vector3D vn1, Vector3D vn2, Vector3D vn3);

		double rayCollision(const Ray3D& ray) const;
		Vector3D getNormal(const Point3D& surfacePoint) const;
		UVCoord get_uv(const Point3D& intersection) const;
		int has_uvs() const;
	private:
		std::vector<double> get_barycentric(const Point3D& intersection) const;
		
		std::vector<const Vertex*> vertices_; //limit 3. Order determines normal face normal direction.
		std::vector<Vector3D> vertex_normals_;
		std::vector<UVCoord> uvs_;

		//Barycentric coordinates. p0 = vertices_.at(0)
		Vector3D e1_; //p1 - p0
		Vector3D e2_; //p2 - p0
		Vector3D normal_; //e1 X e2
	};

}