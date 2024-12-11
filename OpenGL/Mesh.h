#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Shader;

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh();

	void SetPosition(glm::vec3 _position) { position = _position; }
	glm::vec3 GetPosition() { return position; }
	void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }
	glm::vec3 GetRotation() { return rotation; }
	void SetScale(glm::vec3 _scale) { scale = _scale; }
	glm::vec3 GetScale() const { return scale; }
	void SetColor(glm::vec3 _color) { color = _color; }
	void SetSpecularColor(glm::vec3 _specularColor) { specularColor = _specularColor; }
	glm::vec3 GetSpecularColor() const { return specularColor; }

	glm::vec3 GetColor() { return color; }
	void SetLightDirection(glm::vec3 _lightDirection) { lightDirection = _lightDirection; }
	glm::vec3 GetLightDirection() { return lightDirection; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { cameraPosition = _cameraPosition; }

	void Create(Shader* _shader, std::string _file, int _instanceCount = 1);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 _pv);

private:
	void LoadOBJ(std::string& _file);
	void LoadASE(std::string& _file);

	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	std::string Concat(const std::string& _s1, int _index, const std::string& _s2);
	std::string RemoveFolder(std::string& _map);
	void CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);
	bool EndsWith(const std::string& _str, const std::string& _suffix);

private:
	Shader* shader = nullptr;
	Texture textureDiffuse {};
	Texture textureSpecular {};
	Texture textureNormal{};
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	GLuint instanceBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLubyte> indexData;
	std::vector<GLfloat> instanceData;
	bool enableNormalMaps = false;

	int instanceCount = 0;
	bool enableInstancing = false;

	int vertexStride = 0;
	glm::mat4 world = glm::mat4(1);
	glm::vec3 position { 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale { 1.0f, 1.0f, 1.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };
	glm::vec3 specularColor{ 1.0f, 1.0f, 1.0f };

	glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };

	glm::vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };
};
#endif