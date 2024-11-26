#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh();

	void SetPosition(glm::vec3 _position) { position = _position; }
	glm::vec3 GetPosition() { return position; }
	void SetScale(glm::vec3 _scale) { scale = _scale; }
	void SetLightPosition(glm::vec3 _lightPosition) { lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightColor) { lightColor = _lightColor; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { cameraPosition = _cameraPosition; }

	void Create(Shader* _shader);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 _pv);

private:
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();

private:
	Shader* shader = nullptr;
	Texture texture {};
	Texture texture2 {};
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLubyte> indexData;

	glm::mat4 world = glm::mat4(1);
	glm::vec3 position { 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale { 1.0f, 1.0f, 1.0f };

	glm::vec3 lightPosition{ 0.0f, 0.0f, 0.0f };
	glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
	glm::vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };
};
#endif