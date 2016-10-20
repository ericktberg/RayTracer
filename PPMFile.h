/*	
	** PPMFile.h **
	Erick Berg : 9/17/2016
	Abstraction for an ASCII PPM File.
*/

#pragma once

#include "RGBColor.h"
#include "ImageFile.h"
#include "RenderFrame.h"
#include <string>

class PPMFile : public ImageFile
{
	public:
		PPMFile();

		~PPMFile();

		// Get Protected members from superclass ImageFile
		int getMaxVal();

		// Writes a width*height dimension array to the destination file

		void writeToFile(RenderFrame* frame, std::string destination, int max_val);
		void readFile(std::string file_name);
	private:
		std::string type;

		// Helper functions for writeToFile
		std::string ppmHeader(int width, int height, int max_val);
		std::string convertImage(RGBColor* image, int width, int height);
};

