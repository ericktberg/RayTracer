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
		int parseSingle(std::stringstream* ss, double* x);
		int parseDuple(std::stringstream* ss, double* x, double* y);
		int parseTriple(std::stringstream* ss, double* x, double* y, double* z);

		int parseDuple(std::stringstream* ss, int* x, int* y);
		int parseTriple(std::stringstream* ss, int* x, int* y, int* z);

};

