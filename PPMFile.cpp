#pragma once
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

PPMFile::PPMFile(string dest, int maxV) : ImageFile(dest, maxV)
{
	type = "P3";
}

PPMFile::~PPMFile()
{
}

int PPMFile::getMaxVal(){
	return ImageFile::getMaxVal();
}

void PPMFile::writeToFile(RenderFrame* frame){
	ofstream saveFile(destination + ".ppm");
	RGBColor* image = frame->getPixelBuf();
	int width = frame->getWidth();
	int height = frame->getHeight();
	saveFile << ppmHeader(width, height) << convertImage(image, width, height);
	saveFile.close();
}

string PPMFile::ppmHeader(int width, int height){
	stringstream header;
	header << type << "\n" << width << " " << height << "\n" << maxVal << "\n";
	return header.str();
}

string PPMFile::convertImage(RGBColor* image, int width, int height){
	stringstream outputImage;
	for (int i = 0; i < width*height; i++){
		outputImage << image[i].rConvert(maxVal) << " " << image[i].gConvert(maxVal) << " " << image[i].bConvert(maxVal) << "\n";
	}
	return outputImage.str();
}