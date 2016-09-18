#include "PPMFile.h"
#include "ImageFile.h"
#include "RGBImageGenerator.h"
#include "RGBColor.h"
#include "ImageDescriptParser.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	string inputFile = "";
	cout << "Enter the image description file: ";
	cin >> inputFile;
	ImageDescriptParser parser(inputFile);

	PPMFile ppm(parser.getFileStripped());
	while (	parser.parse(&ppm) ) {
		cout << "no file exists. Enter another: ";
		cin >> inputFile;
		parser.setSource(inputFile);
		ppm.setOutputFile(parser.getFileStripped());
	}

	RGBImageGenerator image(ppm.getWidth(), ppm.getHeight(), ppm.getMaxVal());
	RGBColor top = { 0, 0, 0 };
	RGBColor bottom = { 255, 255, 255 };

	ppm.writeToFile(image.generateGradient(top, bottom));

	return 0;
}