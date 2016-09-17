#pragma once
#include <string>
#include <sstream>
#include <istream>

class ParseTXT
{
	public:
		ParseTXT();
		~ParseTXT();
		void openTXT();
		void tokenizeTXT();

	private:
		std::string source;
};

