#include "ImageFile.h"

#include <string>

using namespace std;

ImageFile::ImageFile(){}

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

void ImageFile::readFile(std::string file_name){
	return;
}

RGBColor ImageFile::get_pixel(object::UVCoord uvs) const{
	int i = round(uvs.u * (width - 1));
	int j = round(uvs.v * (height - 1));

	return image.at(j*width + i);
}

void ImageFile::setImageParams(int w, int h, int maxV){
	width = w;
	height = h;
	maxVal = maxV;
}