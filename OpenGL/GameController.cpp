#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#ifndef USE_TOOL_WINDOW
#include "ToolWindow1.h"
#endif
#include "Font.h"

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 });
}
void GameController::RunGame() {
#ifdef USE_TOOL_WINDIOW
    OpenGL::ToolWindow1^ window = gcnew OpenGL::ToolWidnow1();
    if (showToolWindows)
    {
        window->Show();
    }
#endif
    
    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
    shaderSkybox = Shader();
    shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");

    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 5.0f, 0.0f, 0.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);

    Mesh* Suzanne = new Mesh();
    Suzanne->Create(&shaderDiffuse, "../Assets/Models/Suzanne.obj");
    Suzanne->SetCameraPosition(camera.GetPosition());
    Suzanne->SetScale({ 1.0f, 1.0f, 1.0f });
    Suzanne->SetPosition({ 5.0f, 0.0f, 0.0f });
    meshBoxes.push_back(Suzanne);

    Mesh* box = new Mesh();
    box->Create(&shaderDiffuse, "../Assets/Models/Cube.obj");
    box->SetCameraPosition(camera.GetPosition());
    box->SetScale({ 1.0f, 1.0f, 1.0f });
    box->SetPosition({ 5.0f, 0.0f, 0.0f });
    meshBoxes.push_back(box);

    #pragma region Skybox Setup
    skybox = new Skybox();
    skybox->Create(&shaderSkybox, "../Assets/Models/Skybox.obj",
        { "../Assets/Textures/Skybox/right.jpg",
          "../Assets/Textures/Skybox/left.jpg",
          "../Assets/Textures/Skybox/top.jpg",
          "../Assets/Textures/Skybox/bottom.jpg",
          "../Assets/Textures/Skybox/front.jpg",
          "../Assets/Textures/Skybox/back.jpg" });
    #pragma endregion

    Font* arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);

#pragma region Multiple Lights and Multiple Meshes (Commented Out)
  /*  for (int i = 0; i < 4; i++)
    {
        Mesh* light = new Mesh();
        light->Create(&shaderColor);
        light->SetPosition({ 1.0f, 0.0f, -0.35f + (float)i * 0.2f });
        light->SetLightDirection(glm::normalize(glm::vec3({ 0.0f, 0.0f, -0.35f + (float)i * 0.2f }) - light->GetPosition()));
        light->SetColor({ glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f) });
        light->SetScale({ 0.1f, 0.1f, 0.1f });
        lights.push_back(light);
    }

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            Mesh* box = new Mesh();
            box->Create(&shaderDiffuse);
            box->SetCameraPosition(camera.GetPosition());
            box->SetScale({ 0.1f, 0.1f, 0.1f });
            box->SetPosition({ 0.0f, -0.5f + row * 0.1f, -0.5f + col * 0.1f });
            meshBoxes.push_back(box);
        }
        
    }*/
#pragma endregion


    GLFWwindow* win = WindowController::GetInstance().getWindow();
    do {
#pragma region Wiform (ifdef USE_TOOL_WINDOW used)
#ifdef USE_TOOL_WINDOW
        System::Windows::Forms::Application::DoEvents();
#endif
#pragma endregion

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Rotate();
        glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
        skybox->Render(camera.GetProjection() * view);
        for (auto light : lights)
        {
            light->Render(camera.GetProjection() * camera.GetView());
        }
        glm::vec3 rotationSpeed = { 0.0f, 0.005f, 0.0f };
        for (auto box : meshBoxes)
        {
            box->SetRotation(box->GetRotation() + rotationSpeed);
            box->Render(camera.GetProjection() * camera.GetView());
        }

        arialFont->RenderText("Hello World", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });
        glfwSwapBuffers(win);
        glfwPollEvents();
    } 
    while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(win) == 0);

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    lights.clear();
    for (auto box : meshBoxes)
    {
        box->Cleanup();
        delete box;
    }
    meshBoxes.clear();

    shaderFont.Cleanup();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();
}