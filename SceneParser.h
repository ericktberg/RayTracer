#pragma once
#include "Camera.h"
#include "Parser.h"
#include "RenderEngine.h"
#include "RenderFrame.h"
#include "Scene.h"

#include <string>
#include <sstream>
class SceneParser : Parser
{
	public:
		SceneParser();
		~SceneParser();

		int parseSceneFile(RenderEngine* renderTarget, Scene* sceneTarget, Camera* cameraTarget, RenderFrame* frameTarget, std::string inputFile);

	private:
		int parseSphere(std::stringstream* ss, double* x, double* y, double* z, double* radius);
		int parseEllipse(std::stringstream* ss, double* x, double* y, double* z, double* a, double* b, double* c);
		int parsePhongMtl(std::stringstream* ss, double* dr, double* dg, double* db, double* sr, double* sg, double* sb, double* a, double* d, double* s, double* n);
		int parseLight(std::stringstream* ss, double* x, double* y, double* z, double* w, double* r, double* g, double* b);
};

