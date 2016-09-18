/* 
	** ImageFile.h **
	Erick Berg : 9/17/2016
	Abstraction of an ImageFile. Holds metaData pertaining to generic image files.
*/

#pragma once
#include <string>
#include "RGBColor.h"

class ImageFile
{
	public:
		ImageFile(std::string destination);
		ImageFile(std::string destination, int width, int height, int maxVal);
		virtual ~ImageFile();

		int getWidth();
		int getHeight();
		int getMaxVal();
		void setOutputFile(std::string newDest);
		void setImageParams(int width, int height, int maxVal);

	protected:
		std::string destination;

		int width;
		int height;
		int maxVal;
};

