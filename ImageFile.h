/* 
	** ImageFile.h **
	Erick Berg : 9/17/2016
	Abstraction of an ImageFile. Holds metaData pertaining to generic image files.
*/

#pragma once
#include <string>
#include "RGBColor.h"
#include "UVCoord.h"

#include <vector>

class ImageFile
{
	public:
		ImageFile();
		virtual ~ImageFile();

		int getWidth();
		int getHeight();
		int getMaxVal();
		void setOutputFile(std::string newDest);
		void setImageParams(int width, int height, int maxVal);

		virtual void readFile(std::string input);
		virtual RGBColor get_pixel(object::UVCoord uvs) const;

	protected:
		// Image parameters
		std::vector<RGBColor> image;
		int width;
		int height;
		int maxVal;
};

