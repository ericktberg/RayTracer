#include "Scene.h"
#include "Sphere.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>

using namespace std;

Scene::Scene(RGBColor bkg) : numObjects(0), numLights(0), numMaterials(0), num_vertices_(0), num_textures_(-1), bkgColor(bkg)
{
}

Scene::~Scene()
{
	std::for_each(sceneObjects.begin(), sceneObjects.end(), std::default_delete<object::Object>());
	std::for_each(sceneMaterials.begin(), sceneMaterials.end(), std::default_delete<Material>());
	std::for_each(sceneLights.begin(), sceneLights.end(), std::default_delete<light::Light>());
	std::for_each(vertices_.begin(), vertices_.end(), std::default_delete<object::Vertex>());

}

const Material* Scene::material_of(int objectIndex) const{
	int materialIndex = materialMap.at(objectIndex);
	return sceneMaterials[materialIndex];
}

int Scene::texture_index_of(int objectIndex) const {
	if (num_textures_ < 0){
		return -1;
	}

	int texture_index = texture_map_.at(objectIndex);
		
	return texture_index;
}

void Scene::add_vertex(object::Vertex* new_vertex){
	vertices_.push_back(new_vertex);
	num_vertices_++;
}

void Scene::addMaterial(Material* newMaterial){
	sceneMaterials.push_back(newMaterial);
	currentMaterial = numMaterials;
	numMaterials++;
}

void Scene::add_texture(PPMFile* newTexture){
	num_textures_++;
	scene_textures_.push_back(newTexture);
	current_texture_ = num_textures_;
}

void Scene::addLight(light::Light* newLight){
	newLight->calc_samples();
	sceneLights.push_back(newLight);
	numLights++;
}
void Scene::addObject(object::Object* newObject){
	sceneObjects.push_back(newObject);
	materialMap[numObjects] = currentMaterial;
	if (current_texture_ >= 0){
		texture_map_[numObjects] = current_texture_;
	}
	numObjects++;
}