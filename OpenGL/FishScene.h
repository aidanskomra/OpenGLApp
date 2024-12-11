#ifndef FISH_SCENE_H
#define FISH_SCENE_H

#include "Scene.h"
#include "Shader.h"
#include "PostProcessor.h"

class FishScene : public Scene {
public:
    ~FishScene() override = default;

    void Initialize() override;
    void Update(GLFWwindow* window) override;
    void Render() override;
    void Cleanup() override;

    void SetFrequency(float freq) { frequency = freq; }
    void SetAmplitude(float amp) { amplitude = amp; }
    void SetTintBlue(bool tint) { tintBlue = tint; }
    void SetWireframe(bool wire) { wireframe = wire; }

private:
    Shader shaderColor;
    Shader shaderDiffuse;
    Shader shaderPost;
    PostProcessor postProcessor;
    Mesh* fishMesh = nullptr;

    float frequency = 1.0f;
    float amplitude = 0.1f;
    bool tintBlue = false;
    bool wireframe = false;
};

#endif // FISH_SCENE_H
