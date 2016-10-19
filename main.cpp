#pragma once

#include "Camera.h"
#include "ImageDescriptParser.h"
#include "ImageFile.h"
#include "Object.h"
#include "Point3D.h"
#include "PPMFile.h"
#include "RenderEngine.h"
#include "RenderFrame.h"
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
	//does not work anymore due to RenderFrame changes
	//ppm.writeToFile(image.generateGradient(top, bottom));
}

void Assignment1(){

}

int main(int argc, char* argv[]){
	if (argc < 2){
		//TODO: Better message
		cerr << "Include input file name\n" << "RENDER ABORTED";
		return -1;
	}
	string inputFile = argv[1];
	string outputFile = inputFile.substr(0, inputFile.length() - 4);


	SceneParser parser;

	//Objects to parse file contents into.
	RenderEngine renderer;
	Scene myScene;
	Camera mainCam;
	RenderFrame frame;

	if (parser.parseSceneFile(&renderer, &myScene, &mainCam, &frame, inputFile)){
		cout << "RENDER ABORTED";
		return 0;
	}

	//TODO: incorporate only 1 description of height/width in render constructor.
	PPMFile ppm(outputFile, 255);

	ppm.writeToFile(renderer.render(&mainCam, myScene, &frame));
	return 0;
}