/*	
	** PPMFile.h **
	Erick Berg : 9/17/2016
	Abstraction for an ASCII PPM File.
*/

#pragma once

#include "RGBColor.h"
#include "ImageFile.h"
#include <string>

class PPMFile : public ImageFile
{
	public:
		PPMFile(std::string destination);
		PPMFile(std::string destination, int width, int height, int maxVal);

		~PPMFile();

		// Get Protected members from superclass ImageFile
		int getWidth();
		int getHeight();
		int getMaxVal();

		// Writes a width*height dimension array to the destination file

		//TODO: gets width and height from params.
		void writeToFile(RGBColor* image);

	private:
		std::string type;

		// Helper functions for writeToFile
		std::string ppmHeader();
		std::string convertImage(RGBColor* image);
};

