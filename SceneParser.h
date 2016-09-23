#pragma once
#include "Camera.h"
#include "RenderEngine.h"
#include "Scene.h"

#include <string>
class SceneParser
{
public:
	//TODO: THIS!
	SceneParser();
	~SceneParser();

	int parseSceneFile(RenderEngine* renderTarget, Scene* sceneTarget, Camera* cameraTarget, std::string inputFile);
};

