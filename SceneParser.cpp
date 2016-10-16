#include "SceneParser.h"

#include "Camera.h"
#include "Point3D.h"
#include "RenderEngine.h"
#include "RenderFrame.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector3D.h"


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

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
	cout << *dr << *dg << *db << *sr << *sg << *sb << *a << *d << *s << *n;
	return ss->fail();
}
int SceneParser::parseLight(std::stringstream* ss, double* x, double* y, double* z, double* w, double* r, double* g, double* b){
	*ss >> *x >> *y >> *z >> *w >> *r >> *b >> *g;
	return ss->fail();
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
				sceneTarget->setBkgColor(rgb);
			}
			if (firstWord == "mtlcolor"){
				double dr, dg, db, sr, sg, sb, a, d, s, n;
				if (parsePhongMtl(&ss, &dr, &dg, &db, &sr, &sg, &sb, &a, &d, &s, &n)){
					cerr << "Line: " << lineCount << "::Phong Material formatted improperly::\n    Syntax: mtlcolor [dr] [dg] [db] [sr] [sg] [sb] [a] [d] [s] [n]\n";
					return -1;
				}
				sceneTarget->addMaterial(new Material({ dr, dg, db }, { sr, sg, sb }, a, d, s, n));
			}
			if (firstWord == "sphere"){
				double cx, cy, cz, r;
				if (parseSphere(&ss, &cx, &cy, &cz, &r)){
					cerr << "Line: " << lineCount << "::Sphere formatted improperly::\n\tSyntax: sphere [x] [y] [z] [radius]\n";
					return -1;
				}
				Point3D center = { cx, cy, cz };
				sceneTarget->addObject(new Sphere(center, r, currentMtlColor));
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
				}
				sceneTarget->addLight(new Light(x, y, z, w, { r, g, b }));
			}
			lineCount++;
		}

		cout << viewdir.x << endl;
		//Handle improper input
		if (viewdir.isParallel(updir)){
			cout << "Updir and Viewdir are coincident.\n";
			return -1;
		}

		cameraTarget->resetParams(eye, viewdir, updir, 1, fovV);
		return 0;
	}
	else{
		return -1;
	}
}