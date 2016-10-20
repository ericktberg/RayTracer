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
#include "Vertex.h"

#include <map>
#include <vector>

class Scene
{
	public:
		
		// New scene with specified background color
		Scene(RGBColor bkg = { 0, 0, 0 });
		~Scene();

		void add_vertex(object::Vertex* new_vertex);
		void addObject(object::Object* newObject);
		void addLight(light::Light* newLight);
		void addMaterial(Material* newMaterial);
		void add_texture(PPMFile* new_texture);

		void set_bkg_color(RGBColor rgb) { bkgColor = rgb; };

		// Accessors
		RGBColor get_bkg_color() const { return bkgColor; };

		int num_vertices()		const { return num_vertices_; };
		int get_num_objects()	const {	return numObjects; };
		int get_num_lights()	const { return numLights; };
		int get_num_materials() const { return numMaterials; };

		const object::Vertex* vertex_at(int vertexID) const { return vertices_.at(vertexID-1); }; // Takes indices 1:inf
		const object::Object* object_at(int objectID) const { return sceneObjects.at(objectID); };
		const light::Light* light_at(int lightID) const { return sceneLights.at(lightID); };
		const PPMFile* texture_at(int textureID) const { return scene_textures_.at(textureID); };

		const Material* material_of(int objectIndex) const;
		int texture_index_of(int objectIndex) const;

	private:

		std::vector<light::Light*> sceneLights;
		int numLights;

		std::vector<object::Object*> sceneObjects; // Array containing all scene objects
		int numObjects; // number of objects in Scene. (Used in rendering)

		std::vector<Material*> sceneMaterials;
		int numMaterials;

		std::vector<object::Vertex*> vertices_;
		int num_vertices_;

		int currentMaterial;
		std::map<int, int> materialMap;

		int current_texture_;
		int num_textures_;
		std::vector<PPMFile*> scene_textures_;
		std::map<int, int> texture_map_;

		RGBColor bkgColor; //Fill color of background
};

