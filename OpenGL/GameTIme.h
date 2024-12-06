#pragma once

#include "StandardIncludes.h"

class GameTime : public Singleton<GameTime>
{
public:
	void Initialize();
	void Update();

	int FrameCount() { return frameCount; }
	int Fps() { return fps; }
	double DeltaTime() { return deltaTime; }
	double StartTime() { return startTime; }
	double CurrentTime() { return currentTime; }

private:
	int frameCount = 0;
	double deltaTime = 0.0;
	double startTime = 0.0;
	double currentTime = 0.0;

	int fps = 0;
	int fpsCounter = 0;
	double lastTime = 0.0;
};