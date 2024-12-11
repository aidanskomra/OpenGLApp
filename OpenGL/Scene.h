#ifndef SCENE_H
#define SCENE_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void Initialize() = 0;
    virtual void Update(GLFWwindow* window) = 0;
    virtual void Render() = 0;
    virtual void Cleanup() = 0;
    std::vector<Mesh*>& GetLights() { return lights; }

protected:
    Camera camera;
    std::vector<Mesh*> meshes;
    std::vector<Mesh*> lights;
};

#endif // SCENE_H
