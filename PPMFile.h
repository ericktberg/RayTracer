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
		PPMFile(std::string destination);
		PPMFile(std::string destination, int maxVal);

		~PPMFile();

		// Get Protected members from superclass ImageFile
		int getMaxVal();

		// Writes a width*height dimension array to the destination file

		//TODO: gets width and height from params.
		void writeToFile(RenderFrame* frame);

	private:
		std::string type;

		// Helper functions for writeToFile
		std::string ppmHeader(int width, int height);
		std::string convertImage(RGBColor* image, int width, int height);
};

