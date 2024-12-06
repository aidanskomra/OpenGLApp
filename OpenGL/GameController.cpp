#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "GameTIme.h"
#ifndef USE_TOOL_WINDOW
#include "ToolWindow1.h"
#endif
#include "Font.h"

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    srand(time(0));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 5, 5, 5 }, { 0, 0, 0 }, { 0, 1, 0 });
}
void GameController::RunGame() {
#ifdef USE_TOOL_WINDIOW
    OpenGL::ToolWindow1^ window = gcnew OpenGL::ToolWidnow1();
    if (showToolWindows)
    {
        window->Show();
    }
#endif
 
    #pragma region Shader Setup
    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
    shaderSkybox = Shader();
    shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
    shaderPost = Shader();
    shaderPost.LoadShaders("Postprocessor.vertexshader", "Postprocessor.fragmentshader");
#pragma endregion

    #pragma region Post Processes
    postProcessor = PostProcessor();
    postProcessor.Create(&shaderPost);
#pragma endregion

    #pragma region Light
    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 3.0f, 0.0f, 0.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);
#pragma endregion
    
    Mesh* mesh = nullptr;

    #pragma region Fighter (Commented Out)
   /* mesh = new Mesh();
    mesh->Create(&shaderDiffuse, "../Assets/Models/Fighter.obj");
    mesh->SetCameraPosition(camera.GetPosition());
    mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    mesh->SetScale({ 0.002f, 0.002f, 0.002f });
    meshes.push_back(mesh); */
#pragma endregion

    #pragma region Brick Wall (Commented out)
   /* Mesh* box = new Mesh();
    box->Create(&shaderDiffuse, "../Assets/Models/Wall.obj");
    box->SetCameraPosition(camera.GetPosition());
    box->SetPosition({ 0.0f, 0.0f, 0.0f });
    box->SetScale({ 1.0f, 1.0f, 1.0f });
    meshes.push_back(box); */
#pragma endregion

    #pragma region Monkey (Commented Out)
   /* Mesh* Suzanne = new Mesh();
    Suzanne->Create(&shaderDiffuse, "../Assets/Models/Suzanne.obj");
    Suzanne->SetCameraPosition(camera.GetPosition());
    Suzanne->SetScale({ 1.0f, 1.0f, 1.0f });
    Suzanne->SetPosition({ 5.0f, 0.0f, 0.0f });
    meshBoxes.push_back(Suzanne); */
#pragma endregion

    #pragma region Cube (Commented Out)
        Mesh* box = new Mesh();
        box->Create(&shaderDiffuse, "../Assets/Models/Cube.obj", 1000);
        box->SetCameraPosition(camera.GetPosition());
        box->SetScale({ 0.1f, 0.1f, 0.1f });
        box->SetPosition({ 0.0f, 0.0f, 0.0f });
        meshes.push_back(box);
#pragma endregion

    #pragma region Skybox Setup (Commented Out)
    /*
    skybox = new Skybox();
    skybox->Create(&shaderSkybox, "../Assets/Models/Skybox.obj",
        { "../Assets/Textures/Skybox/right.jpg",
          "../Assets/Textures/Skybox/left.jpg",
          "../Assets/Textures/Skybox/top.jpg",
          "../Assets/Textures/Skybox/bottom.jpg",
          "../Assets/Textures/Skybox/front.jpg",
          "../Assets/Textures/Skybox/back.jpg" });
          */
    #pragma endregion

    #pragma region Font Setup
    Font* arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);
#pragma endregion

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

    GameTime::GetInstance().Initialize();
    GLFWwindow* win = WindowController::GetInstance().getWindow();

    const char* effectNames[] = {
        "None", "Grayscale", "Inversion", "Edge Detection", "Custom Effect"
    };

    bool upKeyPressed = false;
    bool downKeyPressed = false;

    do {
#pragma region Wiform (ifdef USE_TOOL_WINDOW used)
#ifdef USE_TOOL_WINDOW
        System::Windows::Forms::Application::DoEvents();
#endif
#pragma endregion

        if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
            if (!upKeyPressed) {
                currentEffect = static_cast<PostProcessingEffect>(
                    (static_cast<int>(currentEffect) + 1) % 5);
                upKeyPressed = true;
            }
        }
        else {
            upKeyPressed = false;
        }

        if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
            if (!downKeyPressed) {
                currentEffect = static_cast<PostProcessingEffect>(
                    (static_cast<int>(currentEffect) - 1 + 5) % 5);
                downKeyPressed = true;
            }
        }
        else {
            downKeyPressed = false;
        }

        glUseProgram(shaderPost.GetProgramID());
        glUniform1i(glGetUniformLocation(shaderPost.GetProgramID(), "effectType"), static_cast<int>(currentEffect));

        GameTime::GetInstance().Update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        postProcessor.Start();

        for (auto light : lights)
        {
            light->Render(camera.GetProjection() * camera.GetView());
        }

        //Note we are now using a pointer so we are not doing a shallow copy, we could also use a reference if we were not on the heap
        glm::vec3 rotationSpeed = { 0.0f, 1.0f, 0.0f };
        for (auto box : meshes)
        {
            box->SetRotation(box->GetRotation() + (rotationSpeed * static_cast<float>(GameTime::GetInstance().DeltaTime())));
            box->Render(camera.GetProjection() * camera.GetView());
        }

        postProcessor.End();
        arialFont->RenderText(effectNames[static_cast<int>(currentEffect)], 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });

        glfwSwapBuffers(win); // Swap the front and back buffers
        glfwPollEvents();
    } 
    while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the esc key was pressed
        glfwWindowShouldClose(win) == 0); // Check if the window is closed

    postProcessor.Cleanup();

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    lights.clear();
    for (auto box : meshes)
    {
        box->Cleanup();
        delete box;
    }
    meshes.clear();
    shaderPost.Cleanup();
    shaderSkybox.Cleanup();
    shaderFont.Cleanup();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();
}