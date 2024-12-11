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
}

void FishScene::Update(GLFWwindow* window) {
    shaderPost.SetFloat("time", static_cast<float>(GameTime::GetInstance().StartTime()));
    shaderPost.SetFloat("frequency", frequency);
    shaderPost.SetFloat("amplitude", amplitude);
    shaderPost.SetInt("tintBlue", tintBlue ? 1 : 0);
}

void FishScene::Render() {
    postProcessor.Start();
    for (auto mesh : meshes) {
        mesh->Render(camera.GetProjection() * camera.GetView());
    }

    for (auto light : lights) {
        light->Render(camera.GetProjection() * camera.GetView());
    }
    postProcessor.End();
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
