#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#ifndef USE_TOOL_WINDOW
#include "ToolWindow1.h"
#endif

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 1, 1, 1 }, { 0, 0, 0 }, { 0, 1, 0 });
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

    meshLight = new Mesh();
    meshLight->Create(&shaderColor);
    meshLight->SetPosition({ 0.5f, 0.0f, -0.5f });
    meshLight->SetScale({ 0.1f, 0.1f, 0.1f });

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            Mesh* box = new Mesh();
            box->Create(&shaderDiffuse);
            box->SetLightColor({ 1.0f, 1.0f, 1.0f });
            box->SetLightPosition(meshLight->GetPosition());
            box->SetCameraPosition(camera.GetPosition());
            box->SetScale({ 0.1f, 0.1f, 0.1f });
            box->SetPosition({ 0.0f, -0.5f + (float)row / 10.0f, -0.2f + (float)col / 10.0f });
            meshBoxes.push_back(box);
        }
        
    }

    GLFWwindow* win = WindowController::GetInstance().getWindow();
    do {
#pragma region Wiform (ifdef USE_TOOL_WINDOW used)
#ifdef USE_TOOL_WINDOW
        System::Windows::Forms::Application::DoEvents();
#endif
#pragma endregion

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        meshLight->Render(camera.GetProjection() * camera.GetView());

        for (auto box : meshBoxes)
        {
            box->Render(camera.GetProjection() * camera.GetView());
        }
        glfwSwapBuffers(win);
        glfwPollEvents();
    } 
    while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(win) == 0);

    meshLight->Cleanup();
    for (auto box : meshBoxes)
    {
        box->Cleanup();
        delete box;
    }
    meshBoxes.clear();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();
}