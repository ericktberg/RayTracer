#include "PPMFile.h"
#include "Parser.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

PPMFile::PPMFile(string dest) : ImageFile(dest)
{
	type = "P3";
}

PPMFile::PPMFile(string dest, int w, int h, int maxV) : ImageFile(dest, w, h, maxV)
{
	type = "P3";
}

PPMFile::~PPMFile()
{
}


int PPMFile::getWidth(){
	return ImageFile::getWidth();
}
int PPMFile::getHeight(){
	return ImageFile::getHeight();
}
int PPMFile::getMaxVal(){
	return ImageFile::getMaxVal();
}

void PPMFile::writeToFile(RGBColor* image){
	ofstream saveFile(destination + ".ppm");
	saveFile << ppmHeader() << convertImage(image);
	saveFile.close();
}

string PPMFile::ppmHeader(){
	stringstream header;
	header << type << "\n" << width << " " << height << "\n" << maxVal << "\n";
	return header.str();
}

string PPMFile::convertImage(RGBColor* image){
	stringstream outputImage;
	for (int i = 0; i < width*height; i++){
		outputImage << image[i].r << " " << image[i].g << " " << image[i].b << "\n";
	}
	return outputImage.str();
}