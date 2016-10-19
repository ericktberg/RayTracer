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
		void addLight(light::Light* newLight);
		// Add a new material
		void addMaterial(Material* newMaterial);

		void set_bkg_color(RGBColor rgb) { bkgColor = rgb; };

		// Accessors
		RGBColor get_bkg_color() const { return bkgColor; };
		std::vector<Object*> get_objects() const { return sceneObjects; };
		std::vector<light::Light*> get_lights() const { return sceneLights; };
		std::vector<Material*> get_materials() const { return sceneMaterials; };
		int get_num_objects() const {	return numObjects; };
		int get_num_lights() const { return numLights; };
		int get_num_materials() const { return numMaterials; };

		Object* object_at(int objectID) const { return sceneObjects[objectID]; };
		light::Light* light_at(int lightID) const { return sceneLights[lightID]; };

		Material* material_of(int objectIndex) const;

	private:
		std::vector<light::Light*> sceneLights;
		int numLights;
		std::vector<Object*> sceneObjects; // Array containing all scene objects
		int numObjects; // number of objects in Scene. (Used in rendering)
		std::vector<Material*> sceneMaterials;
		int numMaterials;

		int currentMaterial;
		std::map<int, int> materialMap;

		RGBColor bkgColor; // Fill color of background
};

