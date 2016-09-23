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
#include "SceneParser.h"
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
	RenderEngine renderer;
	SceneParser parser;
	Scene myScene;
	Camera mainCam;
	parser.parseSceneFile(&renderer, &myScene, &mainCam, "assign1a.txt");
	//Camera mainCam({ 0, 0, 0 }, { 0, .5, 1 }, { 0, 0, 1 }, 1, 90);

	//TODO: incorporate only 1 description of height/width in render constructor.
	PPMFile ppm("rendered", renderer.getWidth(), renderer.getHeight(), 255);

	ppm.writeToFile(renderer.render(mainCam, myScene));
	return 0;
}