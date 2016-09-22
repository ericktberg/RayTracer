/* 
	** Parser.h **
	Erick Berg : 9/17/2016
	Set of parsing tools
*/

#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class Parser
{
	public:
		Parser();
		~Parser();

		int parseFile();

		// If source text is a file name, return the name, stripped of extension.
		std::string getFileStripped(std::string sourceText);
	protected:
};

