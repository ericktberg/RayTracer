#include "Scene.h"
#include "Sphere.h"

Scene::Scene(){
	objects = new Object*[128];
	numObjects = 0;
}
Scene::Scene(RGBColor bkg = { 0, 0, 0 }) 
{
	bkgColor = bkg;
	objects = new Object*[128];
	numObjects = 0;
}

Scene::~Scene()
{
	// TODO: Debug memory error so objects list stops leaking memory. delete[] and delete currently error out.
}

Object** Scene::getObjects(){
	return objects;
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

void Scene::addObject(Object* newObject){
	objects[numObjects] = newObject;
	numObjects++;
}