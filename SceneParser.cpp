#include "SceneParser.h"

#include "AreaLight.h"
#include "Camera.h"
#include "Point3D.h"
#include "RenderEngine.h"
#include "RenderFrame.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "UVCoord.h"
#include "Vector3D.h"
#include "Vertex.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using std::endl;
using std::stringstream;
using std::string;
using std::ifstream;
using std::cerr;

SceneParser::SceneParser()
{
}


SceneParser::~SceneParser()
{
}

int SceneParser::parseSphere(stringstream* ss, double* x, double* y, double* z, double* radius){
	*ss >> *x >> *y >> *z >> *radius;
	return ss->fail();
}

int SceneParser::parseEllipse(stringstream* ss, double* x, double* y, double* z, double* a, double* b, double* c){
	*ss >> *x >> *y >> *z >> *a >> *b >> *c;
	return ss->fail();
}

int SceneParser::parsePhongMtl(std::stringstream* ss, double* dr, double* dg, double* db, double* sr, double* sg, double* sb, double* a, double* d, double* s, double* n){
	*ss >> *dr >> *dg >> *db >> *sr >> *sg >> *sb >> *a >> *d >> *s >> *n;
	return ss->fail();
}
int SceneParser::parseLight(std::stringstream* ss, double* x, double* y, double* z, double* w, double* r, double* g, double* b){
	*ss >> *x >> *y >> *z >> *w >> *r >> *b >> *g;
	return ss->fail();
}

int SceneParser::parseFace(std::stringstream* ss, int* v1, int* v2, int* v3, int* vt1, int* vt2, int* vt3, int* vn1, int* vn2, int* vn3){
	skip47(ss, v1, vt1, vn1);
	skip47(ss, v2, vt2, vn2);
	skip47(ss, v3, vt3, vn3);
	
	return ss->fail();
}

void SceneParser::skip47(std::stringstream* ss, int* v, int* t, int*n){
	char skip_char;
	*ss >> *v;
	if (!ss->eof()){
		if (ss->peek() == '/'){
			*ss >> skip_char;
			if (ss->peek() != '/'){
				*ss >> *t;
			}

			if (!ss->eof()){
				if (ss->peek() == '/'){
					*ss >> skip_char;
					*ss >> *n;
				}
			}
		}
	}
}

int SceneParser::parseSceneFile(RenderEngine* renderTarget, Scene* sceneTarget, Camera* cameraTarget, RenderFrame* frameTarget, std::string inputFile){
	int lineCount = 1;
	string line = "";
	ifstream inputStream(inputFile);
	if (inputStream.is_open()){
		//Identical color applied until overwritten
		RGBColor currentMtlColor;

		//Camera parameters
		Point3D eye;
		Vector3D viewdir;
		Vector3D updir;
		double fovV;
		std::vector <object::UVCoord> coord_list;
		std::vector <Vector3D> normal_list;
		object::UVCoord uv;

		while (getline(inputStream, line)){
			stringstream ss(line);
			string firstWord = "";

			ss >> firstWord;

			if (firstWord == "eye"){
				double ix, iy, iz;
				if (parseTriple(&ss, &ix, &iy, &iz)){
					cerr << "Line: " << lineCount << "::Eye formatted improperly::\n    Syntax: eye [x] [y] [z]\n";
					return -1;
				}
				eye = { ix, iy, iz };
			}
			if (firstWord == "viewdir"){
				double vx, vy, vz;
				if(parseTriple(&ss, &vx, &vy, &vz)){
					cerr << "Line: " << lineCount << "::Viewdir formatted improperly::\n    Syntax: viewdir [x] [y] [z]\n";
					return -1;
				}
				viewdir = { vx, vy, vz };
			}
			if (firstWord == "updir"){
				double ux, uy, uz;
				if (parseTriple(&ss, &ux, &uy, &uz)){
					cerr << "Line: " << lineCount << "::Updir formatted improperly::\n    Syntax: updir [x] [y] [z]\n";
					return -1;
				}
				updir = { ux, uy, uz };
			}
			if (firstWord == "fovv"){
				if (parseSingle(&ss, &fovV)){
					cerr << "Line: " << lineCount << "::FOV formatted improperly::\n    Syntax: fovv [x]\n";
					return -1;
				}
			}
			if (firstWord == "imsize"){
				int width, height;
				if (parseDuple(&ss, &width, &height)){
					cerr << "Line: " << lineCount << "::Image Dimensions formatted improperly::\n    Syntax: imsize [width] [height]\n";
					return -1;
				}
				//force valid dimensions
				frameTarget->setImageDimensions(abs(height), abs(width));
			}
			if (firstWord == "bkgcolor"){
				double r, g, b;
				if (parseTriple(&ss, &r, &g, &b)){
					cerr << "Line: " << lineCount << "::Background RGB formatted improperly::\n    Syntax: bkgcolor [r] [g] [b]\n";
					return -1;
				}
				RGBColor rgb = { r, g, b };
				rgb.clamp();
				sceneTarget->set_bkg_color(rgb);
			}
			if (firstWord == "mtlcolor"){
				double dr, dg, db, sr, sg, sb, a, d, s, n;
				if (parsePhongMtl(&ss, &dr, &dg, &db, &sr, &sg, &sb, &a, &d, &s, &n)){
					cerr << "Line: " << lineCount << "::Phong Material formatted improperly::\n    Syntax: mtlcolor [dr] [dg] [db] [sr] [sg] [sb] [a] [d] [s] [n]\n";
					return -1;
				}
				sceneTarget->addMaterial(new Material({ dr, dg, db }, { sr, sg, sb }, a, d, s, n));
			}
			if (firstWord == "texture"){
				PPMFile* file = new PPMFile();
				std::string file_name;
				ss >> file_name;
				if (ss.fail()){
					return -1;
				}
				file->readFile(file_name);
				sceneTarget->add_texture(file);
			}
			if (firstWord == "sphere"){
				double cx, cy, cz, r;
				if (parseSphere(&ss, &cx, &cy, &cz, &r)){
					cerr << "Line: " << lineCount << "::Sphere formatted improperly::\n\tSyntax: sphere [x] [y] [z] [radius]\n";
					return -1;
				}
				Point3D center = { cx, cy, cz };
				sceneTarget->addObject(new object::Sphere(center, r, currentMtlColor));
			}
			if (firstWord == "ellipsoid"){
				double x, y, z, a, b, c;
				if (parseEllipse(&ss, &x, &y, &z, &a, &b, &c)){
					cerr << "Line: " << lineCount << "::Ellipsoid formatted improperly::\n    Syntax: ellipsoid [x] [y] [z] [a] [b] [c]\n";
					return -1;
				}
			}
			if (firstWord == "light"){
				double x, y, z, w, r, g, b;
				if (parseLight(&ss, &x, &y, &z, &w, &r, &g, &b)){
					cerr << "Line: " << lineCount << "::Light formatted improperly::\n    Syntax: light [x] [y] [z] [w] [r] [g] [b]\n";
					return -1;
				}
				sceneTarget->addLight(new light::Light(x, y, z, w, { r, g, b }));
			}
			if (firstWord == "v"){
				double vx, vy, vz;
				if (parseTriple(&ss, &vx, &vy, &vz)){
					cerr << "Line: " << lineCount << "::Vertex formatted improperly::\n    Syntax: v [x] [y] [z]" << endl;
					return -1;
				}
				sceneTarget->add_vertex(new object::Vertex(vx, vy, vz));
			}
			if (firstWord == "vt"){
				double u, v;
				if (parseDuple(&ss, &u, &v)){
					cerr << "Line: " << lineCount << "::Vertex Texture Coordinate formatted improperly::\n    Syntax: vt u v" << endl;
					return -1;
				}
				uv = { u, v };
				coord_list.push_back(uv);
			}
			if (firstWord == "vn"){
				double vn1, vn2, vn3;
				if (parseTriple(&ss, &vn1, &vn2, &vn3)){
					return -1;
				}
				Vector3D normal(vn1, vn2, vn3);
				normal_list.push_back(normal);
			}
			if (firstWord == "f"){
				int v1, v2, v3, vt1 = 0, vt2 = 0, vt3 = 0, vn1 = 0 , vn2 = 0, vn3 = 0;
				if (parseFace(&ss, &v1, &v2, &v3, &vt1, &vt2, &vt3, &vn1, &vn2, &vn3)){
					cerr << "Line: " << lineCount << "::Face formatted improperly::\n    Syntax f [v1]/[vt1]/[vn1] [v2]/[vt2]/[vn2] [v3]/[vt3]/[vn3]" << endl;
					return -1;
				}
				if (sceneTarget->num_vertices() < std::max(v1,std::max(v2,v3)) || v1 == v2 || v2 == v3){
					cerr << "Line: " << lineCount << "::Face must have three unique, previously defined vertices." << endl;
					return -1;
				}
				object::UVCoord uv1, uv2, uv3;
				Vector3D norm1, norm2, norm3;

				object::Triangle* newTri = new object::Triangle(sceneTarget->vertex_at(v1), sceneTarget->vertex_at(v2), sceneTarget->vertex_at(v3));
				if (vt1 && vt2 && vt3){
					uv1 = coord_list.at(vt1-1);
					uv2 = coord_list.at(vt2-1);
					uv3 = coord_list.at(vt3-1);
					newTri->add_uv_coords(uv1, uv2, uv3);
				}
				if (vn1 && vn2 && vn3){
					norm1 = normal_list.at(vn1 - 1);
					norm2 = normal_list.at(vn2 - 1);
					norm3 = normal_list.at(vn3 - 1);
					newTri->add_vertex_normals(norm1, norm2, norm3);
				}
				sceneTarget->addObject(newTri);
			}


			lineCount++;
		}

		//Handle improper input
		if (viewdir.isParallel(updir)){
			cerr << "Updir and Viewdir are coincident.\n";
			return -1;
		}

		cameraTarget->resetParams(eye, viewdir, updir, 1, fovV);
		return 0;
	}
	else{
		return -1;
	}
}