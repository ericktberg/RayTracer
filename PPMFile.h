#pragma once

#include "RGBColor.h"
#include <string>
#include <ostream>

class PPMFile
{
	public:
		PPMFile();
		~PPMFile();

		int getWidth();
		int getHeight();
		int getMaxVal();

		void writeToFile();

	private:
		std::string destination;

		std::string type;
		int width;
		int height;
		int maxVal;
		RGBColor* image;	
};

