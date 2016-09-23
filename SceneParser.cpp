#include "SceneParser.h"

#include "Camera.h"
#include "Point3D.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector3D.h"


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

int SceneParser::parseSceneFile(RenderEngine* renderTarget, Scene* sceneTarget, Camera* cameraTarget, std::string inputFile){
	string line = "";
	ifstream inputStream(inputFile);
	if (inputStream.is_open()){
		RGBColor currentMtlColor;

		Point3D eye = { 0, 0, 0 };
		Vector3D viewdir = { 1, 0, 0 };
		Vector3D updir = { 0, 0, 1 };
		double fovV = 45;


		while (getline(inputStream, line)){
			stringstream ss(line);
			string firstWord = "";

			ss >> firstWord;

			if (firstWord == "eye"){
				double ix, iy, iz;
				ss >> ix >> iy >> iz;
				eye = { ix, iy, iz };
			}
			if (firstWord == "viewdir"){
				double vx, vy, vz;
				ss >> vx >> vy >> vz;
				viewdir = { vx, vy, vz };
			}
			if (firstWord == "updir"){
				double ux, uy, uz;
				ss >> ux >> uy >> uz;
				updir = { ux, uy, uz };
			}
			if (firstWord == "fovv"){
				ss >> fovV;
			}			
			if (firstWord == "imsize"){
				int width, height;
				ss >> width >> height;
				renderTarget->setImageDimensions(height, width);
			}
			if (firstWord == "bkgcolor"){
				double br, bg, bb;
				ss >> br >> bg >> bb;
				sceneTarget->setBkgColor({ br, bg, bb });
			}
			if (firstWord == "mtlcolor"){
				double mr, mg, mb;
				ss >> mr >> mg >> mb;
				currentMtlColor = { mr, mg, mb };
			}
			if (firstWord == "sphere"){
				double cx, cy, cz, r;
				ss >> cx >> cy >> cz >> r;
				Point3D center = { cx, cy, cz };
				sceneTarget->addObject(new Sphere(center, r, currentMtlColor));
			}
			if (firstWord == "ellipsoid"){

			}
		}
		cameraTarget->resetParams(eye, viewdir, updir, 1, fovV);
		return 0;
	}
	else{
		return -1;
	}
}