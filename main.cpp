#pragma once

#include "Camera.h"
#include "ImageDescriptParser.h"
#include "ImageFile.h"
#include "Object.h"
#include "Point3D.h"
#include "PPMFile.h"
#include "RenderEngine.h"
#include "RGBColor.h"
#include "RGBImageGenerator.h"
#include "Scene.h"
#include "Vector3D.h"


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


void Assignment0(){
	string inputFile = "";
	cout << "Enter the image description file: ";
	cin >> inputFile;
	ImageDescriptParser parser;

	PPMFile ppm(parser.getFileStripped(inputFile));
	while (parser.parse(&ppm, inputFile)) {
		cout << "no file exists. Enter another: ";
		cin >> inputFile;
	}

	RGBImageGenerator image(ppm.getWidth(), ppm.getHeight(), ppm.getMaxVal());
	RGBColor top = { 0, 0, 0 };
	RGBColor bottom = { 255, 255, 255 };

	ppm.writeToFile(image.generateGradient(top, bottom));
}

void Assignment1(){

}

int main(){
	Camera mainCam({ 0, 0, 0 }, { 0, .5, 1 }, { 0, 0, 1 }, 1, 90);
	cout << "u: " << mainCam.getBasis().u.x << " " << mainCam.getBasis().u.y << " " << mainCam.getBasis().u.z << "\n";
	cout << "v: " << mainCam.getBasis().v.x << " " << mainCam.getBasis().v.y << " " << mainCam.getBasis().v.z << "\n";
	cout << "w: " << mainCam.getBasis().w.x << " " << mainCam.getBasis().w.y << " " << mainCam.getBasis().w.z << "\n\n";

	Plane viewPlane = mainCam.getViewPlane();
	cout << "ul: " << viewPlane.ul.x << " " << viewPlane.ul.y << " " << viewPlane.ul.z << "\n";
	cout << "ur: " << viewPlane.ur.x << " " << viewPlane.ur.y << " " << viewPlane.ur.z << "\n";
	cout << "ll: " << viewPlane.ll.x << " " << viewPlane.ll.y << " " << viewPlane.ll.z << "\n";
	cout << "lr: " << viewPlane.lr.x << " " << viewPlane.lr.y << " " << viewPlane.lr.z << "\n\n";

	//TODO: incorporate only 1 description of height/width in render constructor.
	PPMFile ppm("rendered", 150, 150, 255);


	Scene myScene({ 0, 0, 0 });
	RenderEngine renderer(150, 150);
	ppm.writeToFile(renderer.render(mainCam, myScene));
	return 0;
}