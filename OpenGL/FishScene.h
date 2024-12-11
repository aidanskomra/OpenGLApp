#ifndef FISH_SCENE_H
#define FISH_SCENE_H

#include "Scene.h"
#include "Shader.h"

class FishScene : public Scene {
public:
    ~FishScene() override = default;

    void Initialize() override;
    void Update(GLFWwindow* window) override;
    void Render() override;
    void Cleanup() override;

private:
    Shader shaderColor;
    Shader shaderDiffuse;
    Shader shaderPost;
    Mesh* fishMesh = nullptr;

    void ApplyPostProcessing();
};

#endif // FISH_SCENE_H
