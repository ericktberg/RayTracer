#include "Triangle.h"
#include <cstdlib>
#include <iostream>

namespace object{

	Triangle::Triangle(const Vertex* v1, const Vertex* v2, const Vertex* v3) : Object({ 0, 0, 0 }), e1_(*v2, *v1), e2_(*v3,*v1)
	{
		vertices_.reserve(3);
		uvs_.reserve(3);
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);

		normal_ = e1_.crossProduct(e2_);
	}

	Triangle::~Triangle()
	{
	}
	
	void Triangle::addVertex(const Vertex* new_vertex){
		if (vertices_.size() > 3){
			std::cerr << "Triangles have 3 vertices dummy" << std::endl;
			return;
		}
		vertices_.push_back(new_vertex);
	}
	
	void Triangle::add_uv_coords(UVCoord uv1, UVCoord uv2,  UVCoord uv3){
		uvs_.push_back(uv1);
		uvs_.push_back(uv2);
		uvs_.push_back(uv3);
	}

	void Triangle::add_vertex_normals(Vector3D vn1, Vector3D vn2, Vector3D vn3){
		vertex_normals_.push_back(vn1);
		vertex_normals_.push_back(vn2);
		vertex_normals_.push_back(vn3);
	}

	Vector3D Triangle::getNormal(const Point3D& intersectionPoint) const{
		if (vertices_.size() < 3){
			std::cerr << "Triangles need 3 vertices dummy" << std::endl;
			//TODO make -1 error, and 0 a miss
			return{ 0, 0, 0 };
		}
		if (vertex_normals_.size() == 3){
			//barycentric interpolation on vertex normals
			Vector3D n0 = vertex_normals_.at(0);
			Vector3D n1 = vertex_normals_.at(1);
			Vector3D n2 = vertex_normals_.at(2);
			std::vector<double> greek = get_barycentric(intersectionPoint);
			double alpha = greek.at(0);
			double beta = greek.at(1);
			double gamma = greek.at(2);

			Vector3D n = n0*alpha + n1*beta + n2*gamma;
			n.normalize();
			return n;
		}
		else{
			Vertex a = *vertices_.at(0);
			Vertex b = *vertices_.at(1);
			Vertex c = *vertices_.at(2);
			Vector3D e1(b, a);
			Vector3D e2(c, a);
			if (!e1.length() || !e2.length()){
				std::cerr << "Triangle has side length of 0" << std::endl;
				return{ 0, 0, 0 };
			}
			return e1.crossProduct(e2);
		}		
	}

	std::vector<double> Triangle::get_barycentric(const Point3D& intersection) const{
		std::vector<double> result;
		
		double area_A = normal_.length() / 2;
		Vector3D e3(intersection, *vertices_.at(1));
		Vector3D e4(intersection, *vertices_.at(2));
		double a = e3.crossProduct(e4).length() / 2;
		double b = e4.crossProduct(e2_).length() / 2;
		double c = e1_.crossProduct(e3).length() / 2;

		double alpha = a / area_A;
		double beta = b / area_A;
		double gamma = c / area_A;

		result.push_back(alpha);
		result.push_back(beta);
		result.push_back(gamma);

		return result;
	}


	double Triangle::rayCollision(const Ray3D& ray) const {

		Vertex p0 = *vertices_.at(0);

		double d =	- normal_.x() * normal_.length() * p0.x()
					- normal_.y() * normal_.length() * p0.y()
					- normal_.z() * normal_.length() * p0.z();

		Vector3D direction = ray.direction();
		Point3D origin = ray.origin();

		double t;

		double nominator =	   normal_.x() * normal_.length() * origin.x()
							 + normal_.y() * normal_.length() * origin.y()
							 + normal_.z() * normal_.length() * origin.z()
							 + d;
		double denominator =   normal_.x() * normal_.length() * direction.x()
							 + normal_.y() * normal_.length() * direction.y()
							 + normal_.z() * normal_.length() * direction.z();

		t = -nominator / denominator;
		Point3D intersection = direction.getPointAt(t) + origin;
		std::vector<double> greek = get_barycentric(intersection);
		double alpha = greek.at(0);
		double beta = greek.at(1);
		double gamma = greek.at(2);
		int in = alpha < 1 && beta < 1 && gamma < 1 && abs(alpha + beta + gamma - 1) < .00001;
		if (!in){
			return -1;
		}
		else{
			return t;
		}
	}

	UVCoord Triangle::get_uv(const Point3D& intersection) const{
		std::vector<double> greek = get_barycentric(intersection);
		return uvs_.at(0)*greek.at(0) + uvs_.at(1)*greek.at(1) + uvs_.at(2)*greek.at(2);
	}

	int Triangle::has_uvs() const{
		return uvs_.size() == 3;
	}
}