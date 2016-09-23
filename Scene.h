#pragma once
#include "RGBColor.h"
#include "Object.h"
#include <vector>

class Scene
{
	public:
		Scene();
		Scene(RGBColor bkg);
		~Scene();
		RGBColor getBkgColor();
		int getNumObjects();

		//std::vector<Object> objects;
		Object** objects;
	private:
		RGBColor bkgColor;
		int numObjects;

};

