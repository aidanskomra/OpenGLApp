#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

#include "Scene.h"
#include "Shader.h"
#include "PostProcessor.h"
#include "Skybox.h"
#include "Font.h"

class DefaultScene : public Scene {
public:
    ~DefaultScene() override = default;

    void Initialize() override;
    void Update(GLFWwindow* window) override;
    void Render() override;
    void Cleanup() override;

    void SetTransformActive(bool active) { transformActive = active; }
    void SetTranslateActive(bool active) { translateActive = active; }
    void SetRotateActive(bool active) { rotateActive = active; }
    void SetScaleActive(bool active) { scaleActive = active; }
    void ResetTransform();
    void HandleTransform(GLFWwindow* window);
    void HandleMouseClick(GLFWwindow* window);

    void ResetLightPosition() { lights[0]->SetPosition(initialLightPosition); }
    void SetMoveLightActive(bool isActive) { moveLightActive = isActive; }

    void SetLightPosition(const glm::vec3& position);

private:
    Shader shaderColor;
    Shader shaderDiffuse;
    Shader shaderFont;
    Shader shaderSkybox;
    Shader shaderPost;

    PostProcessor postProcessor;
    Mesh* mesh = nullptr;
    Font* arialFont = nullptr;

    bool transformActive = false;
    bool translateActive = false;
    bool rotateActive = false;
    bool scaleActive = false;

    bool moveLightActive = true;
    glm::vec3 initialLightPosition = { 3.0f, 0.0f, 0.0f };
};

#endif // DEFAULT_SCENE_H
