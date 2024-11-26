#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H



#include <vector>
#include <string>
#include <fstream>

#define USE_TOOL_WINDOW

#ifdef _WIN32
#include <Windows.h>

#define M_ASSERT(_cond, _msg) \
if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }

#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Resolution.h"
#include "Singleton.h"

#endif // STANDARD_INCLUDES_H
