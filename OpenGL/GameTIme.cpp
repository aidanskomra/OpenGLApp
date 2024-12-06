#include "GameTIme.h"

void GameTime::Initialize()
{
	startTime = glfwGetTime();
}

void GameTime::Update()
{
	currentTime = glfwGetTime();
	fpsCounter++;
	if (currentTime - lastTime >= 1.0)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		lastTime += 1.0;
	}
	deltaTime = currentTime - startTime;
	startTime = currentTime;
}