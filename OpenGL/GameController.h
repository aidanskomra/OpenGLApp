#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Scene.h"

class GameController : public Singleton<GameController> {
public:
    GameController() = default;
    virtual ~GameController();

    void Initialize();
    void RunGame();
    void SetCurrentScene(Scene* newScene);
    Scene* GetCurrentScene() const { return currentScene; }
private:
    Scene* currentScene = nullptr;
    GLuint vao;

    void CleanupCurrentScene();
};

#endif // GAME_CONTROLLER_H
