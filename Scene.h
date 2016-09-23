/*
	** Scene.h **
	Erick Berg : 9/22/2016
	Abstraction for a 3d Scene
*/

#pragma once
#include "RGBColor.h"
#include "Object.h"

class Scene
{
	public:
		//Default Scene
		Scene();
		// New scene with specified background color
		Scene(RGBColor bkg);
		~Scene();

		// Add an object to the scene
		void addObject(Object* newObject);

		void setBkgColor(RGBColor rgb);

		// Accessors
		RGBColor getBkgColor();
		Object** getObjects();
		int getNumObjects();


	private:
		//TODO: Implement objects as a vector<object>
		Object** objects; // Array containing all scene objects
		RGBColor bkgColor; // Fill color of background
		int numObjects; // number of objects in Scene. (Used in rendering)

		// TODO: Keep track of colors/materials assigned to objects in Scene rather than by object.
};

