/* 
	** ImageDescriptParser.h **
	Erick Berg : 9/17/2016
	Set of parsing tools to read Image description data.
	Inherits from Parser.h
*/

#pragma once
#include "Parser.h"
#include "ImageFile.h"
#include <string>

class ImageDescriptParser : public Parser
{
	public:
		ImageDescriptParser();
		~ImageDescriptParser();

		int parse(ImageFile* target, std::string sourceText);

	protected:
		
	private:
};

