#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Skybox.h"
#include "PostProcessor.h"

class GameController : public Singleton<GameController>
{
public:
	GameController() = default;
	virtual ~GameController() = default;

	void Initialize();
	void RunGame();
	std::vector<Mesh*>& GetLights() { return lights; }
	const Camera& GetCamera() { return camera; }

private:
	Camera camera = {};
	PostProcessor postProcessor = {};

	Shader shaderColor = {};
	Shader shaderDiffuse = {};
	Shader shaderFont = {};
	Shader shaderSkybox = {};
	Shader shaderPost = {};

	std::vector<Mesh*> meshes;
	std::vector<Mesh*> lights;
	Skybox* skybox = nullptr;

	GLuint vao;
};
#endif