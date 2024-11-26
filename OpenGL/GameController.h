#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController : public Singleton<GameController>
{
public:
	GameController() = default;
	virtual ~GameController() = default;

	void Initialize();
	void RunGame();

private:
	Camera camera = {};

	Shader shaderColor = {};
	Shader shaderDiffuse = {};

	std::vector<Mesh*> meshBoxes;
	Mesh* meshLight = {};
};
#endif