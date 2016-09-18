#include "ImageDescriptParser.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ImageDescriptParser::ImageDescriptParser(string inputFileName) : Parser(inputFileName)
{
}


ImageDescriptParser::~ImageDescriptParser()
{
}

int ImageDescriptParser::parse(ImageFile* target){
	string line = "";
	ifstream inputStream(sourceText);
	if (inputStream.is_open()){
		while (getline(inputStream, line)){
			stringstream ss(line);
			string firstWord = "";

			ss >> firstWord;
			if (firstWord == "imsize"){
				int width, height;
				ss >> width >> height;
				target->setImageParams(width, height, 255);
			}
		}
		return 0;
	}
	else{
		return -1;
	}
}

