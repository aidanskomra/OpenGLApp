#ifndef FISH_SCENE_H
#define FISH_SCENE_H

#include "Scene.h"
#include "Shader.h"
#include "PostProcessor.h"
#include "Font.h"

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
    void SetWireframe(bool enabled) { wireframeEnabled = enabled; }

private:
    Shader shaderColor;
    Shader shaderDiffuse;
    Shader shaderPost;
    Shader shaderFont;
    PostProcessor postProcessor;
    Mesh* fishMesh = nullptr;
    Font* arialFont = nullptr;

    float frequency = 1.0f;
    float amplitude = 0.1f;
    bool tintBlue = false;
    bool wireframeEnabled = false;
};

#endif // FISH_SCENE_H
