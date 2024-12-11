#include "GameController.h"
#include "DefaultScene.h"
#include "FishScene.h"
#include "WindowController.h"
#include "GameTime.h"
#include "ToolWindow1.h"

GameController::~GameController() {
    CleanupCurrentScene();
}

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Initialize and show the tool window
    OpenGL::ToolWindow1^ toolWindow = gcnew OpenGL::ToolWindow1();
    toolWindow->Show();

    // Set the default scene
    SetCurrentScene(new DefaultScene());
}

void GameController::RunGame() {
    GLFWwindow* window = WindowController::GetInstance().getWindow();
    GameTime::GetInstance().Initialize();

    do {
#pragma region ToolWindow
#ifdef USE_TOOL_WINDOW
        System::Windows::Forms::Application::DoEvents();
#endif
#pragma endregion

        GameTime::GetInstance().Update();

        if (currentScene) {
            currentScene->Update(window);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            currentScene->Render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    CleanupCurrentScene();
}

void GameController::SetCurrentScene(Scene* newScene) {
    if (currentScene != nullptr) {
        currentScene->Cleanup(); // Clean up the existing scene
        delete currentScene;
    }
    currentScene = newScene;
    currentScene->Initialize(); // Initialize the new scene
}


void GameController::CleanupCurrentScene() {
    if (currentScene) {
        currentScene->Cleanup();
        delete currentScene;
        currentScene = nullptr;
    }
}

