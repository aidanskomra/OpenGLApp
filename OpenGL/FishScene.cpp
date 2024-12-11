#include "FishScene.h"
#include "WindowController.h"
#include "GameTime.h"

void FishScene::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 });

    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderPost.LoadShaders("Postprocessor.vertexshader", "Postprocessor.fragmentshader");
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

    postProcessor.Create(&shaderPost);

    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 5.0f, 5.0f, 5.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);

    fishMesh = new Mesh();
    fishMesh->Create(&shaderDiffuse, "../Assets/Models/fish.ase");
    fishMesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    fishMesh->SetRotation({ 0.0f, glm::radians(-90.0f), 0.0f });
    fishMesh->SetScale({ 0.25f, 0.25f, 0.25f });
    meshes.push_back(fishMesh);

    arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);
}

void FishScene::Update(GLFWwindow* window) {
    shaderPost.SetFloat("time", static_cast<float>(GameTime::GetInstance().StartTime()));
    shaderPost.SetFloat("frequency", frequency);
    shaderPost.SetFloat("amplitude", amplitude);
    shaderPost.SetInt("tintBlue", tintBlue ? 1 : 0);
}

void FishScene::Render() {
    if (wireframeEnabled) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    postProcessor.Start();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto mesh : meshes) {
        mesh->Render(camera.GetProjection() * camera.GetView());
    }

    for (auto light : lights) {
        light->Render(camera.GetProjection() * camera.GetView());
    }

    arialFont->RenderText("Aidan Skomra - Final Project", 10, 40, 0.3f, { 1.0f, 1.0f, 1.0f });

    arialFont->RenderText("FPS: " + std::to_string(GameTime::GetInstance().Fps()), 10, 90, 0.3f, { 1.0f, 1.0f, 1.0f });

    double mouseX, mouseY;
    glfwGetCursorPos(WindowController::GetInstance().getWindow(), &mouseX, &mouseY);
    arialFont->RenderText("Mouse Pos: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")",
        10, 140, 0.3f, { 1.0f, 1.0f, 1.0f });

    int leftButtonState = glfwGetMouseButton(WindowController::GetInstance().getWindow(), GLFW_MOUSE_BUTTON_LEFT);
    int middleButtonState = glfwGetMouseButton(WindowController::GetInstance().getWindow(), GLFW_MOUSE_BUTTON_MIDDLE);
    arialFont->RenderText("Left Button: " + std::string(leftButtonState == GLFW_PRESS ? "Down" : "Up"),
        10, 190, 0.3f, { 1.0f, 1.0f, 1.0f });
    arialFont->RenderText("Middle Button: " + std::string(middleButtonState == GLFW_PRESS ? "Down" : "Up"),
        10, 240, 0.3f, { 1.0f, 1.0f, 1.0f });

    glm::vec3 position = meshes[0]->GetPosition();
    arialFont->RenderText("Fish Position: (" + std::to_string(position.x) + ", "
        + std::to_string(position.y) + ", " + std::to_string(position.z) + ")",
        10, 290, 0.3f, { 1.0f, 1.0f, 1.0f });

    glm::vec3 rotation = glm::degrees(meshes[0]->GetRotation());
    arialFont->RenderText("Fish Rotation: (" + std::to_string(rotation.x) + ", "
        + std::to_string(rotation.y) + ", " + std::to_string(rotation.z) + ")",
        10, 340, 0.3f, { 1.0f, 1.0f, 1.0f });

    glm::vec3 scale = meshes[0]->GetScale();
    arialFont->RenderText("Fish Scale: (" + std::to_string(scale.x) + ", "
        + std::to_string(scale.y) + ", " + std::to_string(scale.z) + ")",
        10, 390, 0.3f, { 1.0f, 1.0f, 1.0f });

    postProcessor.End();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void FishScene::Cleanup() {
    postProcessor.Cleanup();

    for (auto mesh : meshes) {
        mesh->Cleanup();
        delete mesh;
    }
    meshes.clear();

    for (auto light : lights) {
        light->Cleanup();
        delete light;
    }
    lights.clear();
}
