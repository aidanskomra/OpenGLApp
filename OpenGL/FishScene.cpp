#include "FishScene.h"
#include "WindowController.h"
#include "GameTime.h"

void FishScene::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 });

    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 3.0f, 3.0f, 3.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);

    fishMesh = new Mesh();
    fishMesh->Create(&shaderDiffuse, "../Assets/Models/Fish.ase");
    fishMesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    fishMesh->SetRotation({ 0.0f, glm::radians(-90.0f), 0.0f });
    fishMesh->SetScale({ 200.0f, 200.0f, 200.0f });
    meshes.push_back(fishMesh);
}

void FishScene::Update(GLFWwindow* window) {
    // Optional: Update logic specific to FishScene
}

void FishScene::Render() {
    for (auto mesh : meshes) {
        mesh->Render(camera.GetProjection() * camera.GetView());
    }
    for (auto light : lights) {
        light->Render(camera.GetProjection() * camera.GetView());
    }
}

void FishScene::Cleanup() {
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
