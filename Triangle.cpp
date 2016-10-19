#include "Triangle.h"
#include <iostream>

namespace object{

	Triangle::Triangle(const Vertex* v1, const Vertex* v2, const Vertex* v3) : Object({ 0, 0, 0 })
	{
		vertices_.reserve(3);
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);
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

	Vector3D Triangle::getNormal(const Point3D& intersectionPoint) const{
		if (vertices_.size() < 3){
			std::cerr << "Triangles need 3 vertices dummy" << std::endl;
			//TODO make -1 error, and 0 a miss
			return{ 0, 0, 0 };
		}

		Vertex a = *vertices_.at(0);
		Vertex b = *vertices_.at(1);
		Vertex c = *vertices_.at(2);
		Vector3D e1(b, a);
		Vector3D e2(c, a);
		if (!e1.length() || !e2.length()){
			std::cerr << "Triangle has side length of 0" << std::endl;
			return { 0, 0, 0 };
		}
		return e1.crossProduct(e2);
	}

	double Triangle::rayCollision(const Ray3D& ray) const {

		if (vertices_.size() < 3){
			std::cerr << "Triangles need 3 vertices dummy" << std::endl;
			//TODO make -1 error, and 0 a miss
			return -1;
		}

		//e_ = ray.origin
		//d_ = ray.direction
		//a_ , b_, c_ are vertices.
		const Vertex *a_ = vertices_.at(0);
		const Vertex *b_ = vertices_.at(1);
		const Vertex *c_ = vertices_.at(2);
		Point3D e_ = ray.origin;
		Vector3D d_ = ray.direction;
	
		//ray triangle intersection from Marschner-Shirley text
		//Uses cramers rule to compute barycentric coordinates beta, gamma, and ray distance t
		double a, b, c, d, e, f, g, h, i, j, k, l;
		double beta, gamma, t;

		a = a_->x() - b_->x();
		b = a_->y() - b_->y();
		c = a_->z() - b_->z();
		d = a_->x() - c_->x();
		e = a_->y() - c_->y();
		f = a_->z() - c_->z();
		g = d_.x();
		h = d_.y();
		i = d_.z();
		j = a_->x() - e_.x();
		k = a_->y() - e_.y();
		l = a_->z() - e_.z();

		double det = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

		t =  	-(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / det;
		if (t < 0){
			return t;
		}
		gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / det;
		if (gamma < 0 || gamma > 1){
			return -1;
		}
		beta =	(j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / det;
		if (beta < 0 || beta > 1 - gamma){
			return -1;
		}

		return t;
	}


}