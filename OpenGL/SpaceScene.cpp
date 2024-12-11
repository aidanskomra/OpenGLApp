#include "SpaceScene.h"
#include "WindowController.h"
#include "GameTime.h"
#include "Font.h"
#include <glm/gtc/random.hpp>

void SpaceScene::Initialize() {
    // Setup camera
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

    // Load shaders
    shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    // Load the skybox
    skybox = new Skybox();
    skybox->Create(&shaderSkybox, "../Assets/Models/SkyBox.obj", {
        "../Assets/Textures/Skybox/right.jpg",
        "../Assets/Textures/Skybox/left.jpg",
        "../Assets/Textures/Skybox/top.jpg",
        "../Assets/Textures/Skybox/bottom.jpg",
        "../Assets/Textures/Skybox/front.jpg",
        "../Assets/Textures/Skybox/back.jpg"
        });

    // Load the spaceship
    spaceship = new Mesh();
    spaceship->Create(&shaderDiffuse, "../Assets/Models/Spaceship.ase");
    spaceship->SetPosition({ 0.0f, 0.0f, 0.0f });
    spaceship->SetRotation({ 0.0f, glm::radians(-90.0f), 0.0f });
    spaceship->SetScale({ 0.05f, 0.05f, 0.05f });
    meshes.push_back(spaceship);

    // Create 100 fish with random attributes
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 100; i++) {
        Mesh* fish = new Mesh();
        fish->Create(&shaderDiffuse, "../Assets/Models/Fish.ase");

        // Randomize position, rotation, and scale
        glm::vec3 randomPosition = glm::linearRand(glm::vec3(-10.0f), glm::vec3(10.0f));
        glm::vec3 randomRotation = glm::radians(glm::linearRand(glm::vec3(0.0f), glm::vec3(360.0f)));
        glm::vec3 randomScale = glm::vec3(glm::linearRand(0.01f, 0.05f));

        fish->SetPosition(randomPosition);
        fish->SetRotation(randomRotation);
        fish->SetScale(randomScale);

        meshes.push_back(fish);
    }
}

void SpaceScene::Update(GLFWwindow* window) {
    glm::vec3 rotationSpeed = { 0.0f, 0.1f, 0.0f };

    for (auto mesh : meshes) {
        if (mesh != spaceship) {
            // Rotate only the fish
            mesh->SetRotation(mesh->GetRotation() + rotationSpeed * static_cast<float>(GameTime::GetInstance().DeltaTime()));
        }
    }
}

void SpaceScene::Render() {
    // Render the skybox
    skybox->Render(camera.GetProjection() * camera.GetView());

    // Render the spaceship
    spaceship->Render(camera.GetProjection() * camera.GetView());

    // Render all the fish
    for (auto mesh : meshes) {
        if (mesh != spaceship) {
            mesh->Render(camera.GetProjection() * camera.GetView());
        }
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
}
