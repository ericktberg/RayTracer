#pragma once
#include "PPMFile.h"
#include "ImageFile.h"
#include "RGBImageGenerator.h"
#include "RGBColor.h"
#include "ImageDescriptParser.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Object.h"

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

int main(){
	Object obj;
	Basis3D b = obj.getOrientation();
	Point3D p1 = { 1, 1, 1 };
	Point3D p2 = { 2, 2, 2 };
	Vector3D v = { p1, p2 };
	cout << " " << v.x << " " << v.y << " " << v.z;
	return 0;
}