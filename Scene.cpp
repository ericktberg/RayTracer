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

vector<Object*> Scene::getObjects(){
	return sceneObjects;
}
vector<Light*> Scene::getLights(){
	return sceneLights;
}
vector<Material*> Scene::getMaterials(){
	return sceneMaterials;
}

Material* Scene::materialOf(int objectIndex){
	int materialIndex = materialMap[objectIndex];
	return sceneMaterials[materialIndex];
}


int Scene::getNumObjects(){
	return numObjects;
}

RGBColor Scene::getBkgColor(){
	return bkgColor;
}


void Scene::setBkgColor(RGBColor rgb){
	bkgColor = rgb;
}

void Scene::addMaterial(Material* newMaterial){
	sceneMaterials.push_back(newMaterial);
	currentMaterial = numMaterials;
	numMaterials++;
}
void Scene::addLight(Light* newLight){
	sceneLights.push_back(newLight);
	numLights++;
}
void Scene::addObject(Object* newObject){
	sceneObjects.push_back(newObject);
	materialMap[numObjects] = currentMaterial;
	numObjects++;
}