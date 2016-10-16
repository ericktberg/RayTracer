/*
	** Scene.h **
	Erick Berg : 9/22/2016
	Abstraction for a 3d Scene
*/

#pragma once
#include "Light.h"
#include "Material.h"
#include "RGBColor.h"
#include "Object.h"

#include <map>
#include <vector>

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
		// Add a light to the scene
		void addLight(Light* newLight);
		// Add a new material
		void addMaterial(Material* newMaterial);

		void setBkgColor(RGBColor rgb);

		// Accessors
		RGBColor getBkgColor();
		std::vector<Object*> getObjects();
		std::vector<Light*> getLights();
		std::vector<Material*> getMaterials();
		Material* materialOf(int objectIndex);
		int getNumObjects();
		int getNumLights();
		int getNumMaterials();

	private:
		std::vector<Light*> sceneLights;
		int numLights;
		std::vector<Object*> sceneObjects; // Array containing all scene objects
		int numObjects; // number of objects in Scene. (Used in rendering)
		std::vector<Material*> sceneMaterials;
		int numMaterials;

		int currentMaterial;
		std::map<int, int> materialMap;

		RGBColor bkgColor; // Fill color of background
};

