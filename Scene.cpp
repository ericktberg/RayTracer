#include "Scene.h"
#include "Sphere.h"
#include <algorithm>
#include <memory>

using namespace std;

Scene::Scene(RGBColor bkg) : numObjects(0), numLights(0), numMaterials(0), num_vertices_(0), bkgColor(bkg)
{
}

Scene::~Scene()
{
	std::for_each(sceneObjects.begin(), sceneObjects.end(), std::default_delete<Object>());
	std::for_each(sceneMaterials.begin(), sceneMaterials.end(), std::default_delete<Material>());
	std::for_each(sceneLights.begin(), sceneLights.end(), std::default_delete<light::Light>());
	std::for_each(vertices_.begin(), vertices_.end(), std::default_delete<object::Vertex>());

}

const Material* Scene::material_of(int objectIndex) const{
	int materialIndex = materialMap.at(objectIndex);
	return sceneMaterials[materialIndex];
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
void Scene::addLight(light::Light* newLight){
	newLight->calc_samples();
	sceneLights.push_back(newLight);
	numLights++;
}
void Scene::addObject(Object* newObject){
	sceneObjects.push_back(newObject);
	materialMap[numObjects] = currentMaterial;
	numObjects++;
}