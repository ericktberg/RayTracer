#pragma once
#include <string>

class RGBImageGenerator
{
	public:
		RGBImageGenerator();
		~RGBImageGenerator();

		void generateSolid(std::string r, std::string g, std::string b);
		void generateGradient(int rTop, int gTop, int bTop, int rBottom, int gBottom, int bBottom);
};

