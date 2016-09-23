#include "Scene.h"
#include "Sphere.h"

Scene::Scene(){ }
Scene::Scene(RGBColor bkg = { 0, 0, 0 }) 
{
	bkgColor = bkg;
	objects = new Object*[2];
	objects[0] = new Sphere({ 0, 2, 4 }, 2, { 255, 255, 255 });
	numObjects = 1;
	objects[0]->testObject();
}


Scene::~Scene()
{
	//delete objects[0];
}

int Scene::getNumObjects(){
	return numObjects;
}

RGBColor Scene::getBkgColor(){
	return bkgColor;
}