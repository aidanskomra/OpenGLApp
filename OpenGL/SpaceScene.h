#ifndef SPACE_SCENE_H
#define SPACE_SCENE_H

#include "Scene.h"
#include "Shader.h"
#include "Skybox.h"

class SpaceScene : public Scene {
public:
    ~SpaceScene() override = default;

    void Initialize() override;
    void Update(GLFWwindow* window) override;
    void Render() override;
    void Cleanup() override;

private:
    Shader shaderColor;
    Shader shaderSkybox;
    Shader shaderDiffuse;
    Skybox* skybox = nullptr;
    Mesh* spaceship = nullptr;

    std::vector<Mesh*> meshes; // Contains the spaceship and all fish
};

#endif // SPACE_SCENE_H
