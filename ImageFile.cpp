#include "ImageFile.h"

#include <string>

using namespace std;

ImageFile::ImageFile(string fileName)
{
	destination = fileName;
}

ImageFile::ImageFile(string fileName, int maxV)
{
	destination = fileName;
	maxVal = maxV;
}


ImageFile::ImageFile(string fileName, int w, int h, int maxV)
{
	destination = fileName;
	setImageParams(w, h, maxV);
}


ImageFile::~ImageFile()
{
}

int ImageFile::getWidth(){
	return width;
}
int ImageFile::getHeight(){
	return height;
}
int ImageFile::getMaxVal(){
	return maxVal;
}

void ImageFile::setOutputFile(string newDest){
	destination = newDest;
}
void ImageFile::setImageParams(int w, int h, int maxV){
	width = w;
	height = h;
	maxVal = maxV;
}