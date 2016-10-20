#pragma once
#include "PPMFile.h"
#include "Parser.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

PPMFile::PPMFile() : ImageFile()
{
	type = "P3";
}

PPMFile::~PPMFile()
{
}

int PPMFile::getMaxVal(){
	return ImageFile::getMaxVal();
}

void PPMFile::writeToFile(RenderFrame* frame, std::string destination, int max_val){
	maxVal = max_val;
	ofstream saveFile(destination + ".ppm");
	RGBColor* image = frame->getPixelBuf();
	int width = frame->getWidth();
	int height = frame->getHeight();
	saveFile << ppmHeader(width, height, maxVal) << convertImage(image, width, height);
	saveFile.close();
}

void PPMFile::readFile(std::string file_name){
	stringstream ss;
	string line = "";
	ifstream inputStream(file_name);
	if (inputStream.is_open()){
		int line_count = 0;
		while (getline(inputStream, line)){
			stringstream ss(line);
			if (!line_count){
				ss >> type >> width >> height >> maxVal;
				std::cout << type << " : " << width << " : " << height << " : " << maxVal << std::endl;
			}
			else{
				double r, g, b;
				ss >> r >> g >> b;
				//cout << r << " : " << g << " : " << b << endl;
				image.push_back({ r/maxVal, g/maxVal, b/maxVal });
			}
			line_count++;		
		}
	}
}

string PPMFile::ppmHeader(int width, int height, int maxVal){
	stringstream header;
	header << type << " " << width << " " << height << " " << maxVal << "\n";
	return header.str();
}

string PPMFile::convertImage(RGBColor* image, int width, int height){
	stringstream outputImage;
	for (int i = 0; i < width*height; i++){
		outputImage << image[i].rConvert(maxVal) << " " << image[i].gConvert(maxVal) << " " << image[i].bConvert(maxVal) << "\n";
	}
	return outputImage.str();
}