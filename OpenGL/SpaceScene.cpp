#include "SpaceScene.h"
#include "WindowController.h"
#include "GameTime.h"
#include "Font.h"
#include <glm/gtc/random.hpp>

void SpaceScene::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    skybox = new Skybox();
    skybox->Create(&shaderSkybox, "../Assets/Models/SkyBox.obj", {
        "../Assets/Textures/Skybox/right.png",
        "../Assets/Textures/Skybox/left.png",
        "../Assets/Textures/Skybox/top.png",
        "../Assets/Textures/Skybox/bottom.png",
        "../Assets/Textures/Skybox/front.png",
        "../Assets/Textures/Skybox/back.png"
        });

    spaceship = new Mesh();
    spaceship->Create(&shaderDiffuse, "../Assets/Models/Fighter.ase");
    spaceship->SetPosition({ 0.0f, 0.0f, 0.0f });
    spaceship->SetRotation({ 0.0f, glm::radians(-90.0f), 0.0f });
    spaceship->SetScale({ 0.002f, 0.002f, 0.002f });
    meshes.push_back(spaceship);

    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 3.0f, 0.0f, 0.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetSpecularStrength(0.5f);
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);

    srand(static_cast<unsigned int>(time(0)));
        Mesh* fish = new Mesh();
        fish->Create(&shaderDiffuse, "../Assets/Models/fish.ase", 100);

        for (int i = 0; i < 100; i++) {
        glm::vec3 randomPosition = glm::linearRand(glm::vec3(0.0f), glm::vec3(20.0f));
        glm::vec3 randomRotation = glm::radians(glm::linearRand(glm::vec3(0.0f), glm::vec3(360.0f)));
        glm::vec3 randomScale = glm::vec3(glm::linearRand(0.01f, 0.05f));

        fish->SetPosition(randomPosition);
        fish->SetRotation(randomRotation);
        fish->SetScale(randomScale);

        meshes.push_back(fish);
    }
}

void SpaceScene::Update(GLFWwindow* window) {
    camera.Rotate();

    glm::vec3 rotationSpeed = { 0.0f, 0.1f, 0.0f };

    for (auto mesh : meshes) {
        if (mesh != spaceship) {
            mesh->SetRotation(mesh->GetRotation() + rotationSpeed * static_cast<float>(GameTime::GetInstance().DeltaTime()));
        }
    }
}

void SpaceScene::Render() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));

    skybox->Render(camera.GetProjection() * view);

    for (auto mesh : meshes) {
        mesh->Render(camera.GetProjection() * camera.GetView());
    }
}

void SpaceScene::Cleanup() {
    if (skybox) {
        skybox->Cleanup();
        delete skybox;
        skybox = nullptr;
    }

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
