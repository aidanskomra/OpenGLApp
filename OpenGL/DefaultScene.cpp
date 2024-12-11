#include "DefaultScene.h"
#include "WindowController.h"
#include "GameTime.h"
#include "Font.h"

void DefaultScene::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 });

    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 3.0f, 0.0f, 0.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);

    mesh = new Mesh();
    mesh->Create(&shaderDiffuse, "../Assets/Models/Fighter.ase");
    mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    mesh->SetRotation({ 0.0f, glm::radians(-90.0f), 0.0f });
    mesh->SetScale({ 0.002f, 0.002f, 0.002f });
    meshes.push_back(mesh);

    arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);

}

void DefaultScene::Update(GLFWwindow* window) {
    if (transformActive && mesh != nullptr) {
        HandleTransform(window);
    }
    else if (moveLightActive && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        HandleMouseClick(window);
    }
    
    glm::vec3 rotationSpeed = { -1.0f, 0.0f, 0.0f };
    for (auto box : meshes) {
        box->SetRotation(box->GetRotation() + (rotationSpeed * static_cast<float>(GameTime::GetInstance().DeltaTime())));
    }
}

void DefaultScene::Render() {
    for (auto light : lights) {
        light->Render(camera.GetProjection() * camera.GetView());
    }

    for (auto mesh : meshes) {
        mesh->Render(camera.GetProjection() * camera.GetView());
    }

    // Render project title
    arialFont->RenderText("Aidan Skomra - Final Project", 10, 40, 0.3f, { 1.0f, 1.0f, 1.0f });

    // Render FPS
    arialFont->RenderText("FPS: " + std::to_string(GameTime::GetInstance().Fps()), 10, 90, 0.3f, { 1.0f, 1.0f, 1.0f });

    // Render mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(WindowController::GetInstance().getWindow(), &mouseX, &mouseY);
    arialFont->RenderText("Mouse Pos: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")",
        10, 140, 0.3f, { 1.0f, 1.0f, 1.0f });

    // Render mouse button states
    int leftButtonState = glfwGetMouseButton(WindowController::GetInstance().getWindow(), GLFW_MOUSE_BUTTON_LEFT);
    int middleButtonState = glfwGetMouseButton(WindowController::GetInstance().getWindow(), GLFW_MOUSE_BUTTON_MIDDLE);
    arialFont->RenderText("Left Button: " + std::string(leftButtonState == GLFW_PRESS ? "Down" : "Up"),
        10, 190, 0.3f, { 1.0f, 1.0f, 1.0f });
    arialFont->RenderText("Middle Button: " + std::string(middleButtonState == GLFW_PRESS ? "Down" : "Up"),
        10, 240, 0.3f, { 1.0f, 1.0f, 1.0f });

    // Render mesh position
    glm::vec3 position = meshes[0]->GetPosition(); // Assuming one primary mesh
    arialFont->RenderText("Fighter Position: (" + std::to_string(position.x) + ", "
        + std::to_string(position.y) + ", " + std::to_string(position.z) + ")",
        10, 290, 0.3f, { 1.0f, 1.0f, 1.0f });

    // Render mesh rotation
    glm::vec3 rotation = glm::degrees(meshes[0]->GetRotation());
    arialFont->RenderText("Fighter Rotation: (" + std::to_string(rotation.x) + ", "
        + std::to_string(rotation.y) + ", " + std::to_string(rotation.z) + ")",
        10, 340, 0.3f, { 1.0f, 1.0f, 1.0f });

    // Render mesh scale
    glm::vec3 scale = meshes[0]->GetScale();
    arialFont->RenderText("Fighter Scale: (" + std::to_string(scale.x) + ", "
        + std::to_string(scale.y) + ", " + std::to_string(scale.z) + ")",
        10, 390, 0.3f, { 1.0f, 1.0f, 1.0f });

}

void DefaultScene::Cleanup() {
    for (auto light : lights) {
        light->Cleanup();
        delete light;
    }
    lights.clear();

    for (auto mesh : meshes) {
        mesh->Cleanup();
        delete mesh;
    }
    meshes.clear();

}

void DefaultScene::SetLightPosition(const glm::vec3& position) {
    if (!lights.empty()) {
        lights[0]->SetPosition(position);
    }
}

void DefaultScene::ResetTransform() {
    if (!mesh) return;

    mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    mesh->SetRotation({ 0.0f, glm::radians(-90.0f), 0.0f });
    mesh->SetScale({ 0.002f, 0.002f, 0.002f });
}

void DefaultScene::HandleTransform(GLFWwindow* window) {
    if (!transformActive || mesh == nullptr) return;

    static double lastMouseX = 0.0, lastMouseY = 0.0;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    float deltaTime = static_cast<float>(GameTime::GetInstance().DeltaTime());

    bool leftMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool middleMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    if (leftMousePressed) {
        if (translateActive) {
            glm::vec3 position = mesh->GetPosition();
            position.x += static_cast<float>(deltaX * 9.0f * deltaTime);
            position.y -= static_cast<float>(deltaY * 9.0f * deltaTime);
            mesh->SetPosition(position);
        }

        if (rotateActive) {
            glm::vec3 rotation = mesh->GetRotation();
            rotation.x += static_cast<float>(deltaY * 0.9f * deltaTime);
            rotation.y += static_cast<float>(deltaX * 0.9f * deltaTime);
            mesh->SetRotation(rotation);
        }

        if (scaleActive) {
            glm::vec3 scale = mesh->GetScale();
            scale.x += static_cast<float>(deltaX * 0.003f * deltaTime);
            scale.y += static_cast<float>(deltaY * 0.003f * deltaTime);
            scale = glm::clamp(scale, glm::vec3(0.0001f), glm::vec3(0.05f));
            mesh->SetScale(scale);
        }
    }

    if (middleMousePressed) {
        if (translateActive) {
            glm::vec3 position = mesh->GetPosition();
            position.z += static_cast<float>(deltaY * 9.0f * deltaTime);
            mesh->SetPosition(position);
        }

        if (rotateActive) {
            glm::vec3 rotation = mesh->GetRotation();
            rotation.z += static_cast<float>(deltaY * 0.9f * deltaTime);
            mesh->SetRotation(rotation);
        }

        if (scaleActive) {
            glm::vec3 scale = mesh->GetScale();
            scale.z += static_cast<float>(deltaY * 0.001f * deltaTime);
            scale = glm::clamp(scale, glm::vec3(0.0001f), glm::vec3(0.05f));
            mesh->SetScale(scale);
        }
    }
}


void DefaultScene::HandleMouseClick(GLFWwindow* window) {
    if (!moveLightActive) return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Resolution resolution = WindowController::GetInstance().GetResolution();

    float deltaX = static_cast<float>(mouseX - resolution.width / 2);
    float deltaY = static_cast<float>(resolution.height / 2 - mouseY);
    glm::vec3 movementDirection(-deltaX / resolution.width, deltaY / resolution.height, 0.0f);

    float speed = 0.005f;

    Mesh* light = lights[0];
    glm::vec3 currentPosition = light->GetPosition();

    glm::vec3 newPosition = {
         currentPosition.x,
         currentPosition.y + movementDirection.y * speed,
         currentPosition.z + movementDirection.x * speed
    };


    light->SetPosition(newPosition);

    std::cout << "Updated Light Position: " << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << std::endl;
}