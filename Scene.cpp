#include "Scene.h"
#include "Sphere.h"

using namespace std;

Scene::Scene() : numObjects(0), numLights(0), numMaterials(0)
{
}
Scene::Scene(RGBColor bkg) : numObjects(0), numLights(0), numMaterials(0), bkgColor(bkg)
{
}

Scene::~Scene()
{
}

Material* Scene::material_of(int objectIndex) const{
	int materialIndex = materialMap.at(objectIndex);
	return sceneMaterials[materialIndex];
}

void Scene::addMaterial(Material* newMaterial){
	sceneMaterials.push_back(newMaterial);
	currentMaterial = numMaterials;
	numMaterials++;
}
void Scene::addLight(light::Light* newLight){
	sceneLights.push_back(newLight);
	numLights++;
}
void Scene::addObject(Object* newObject){
	sceneObjects.push_back(newObject);
	materialMap[numObjects] = currentMaterial;
	numObjects++;
}