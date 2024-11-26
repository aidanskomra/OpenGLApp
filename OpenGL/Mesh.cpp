#include "Mesh.h"
#include "Shader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

Mesh::~Mesh()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
	if (indexBuffer != 0)
	{
		glDeleteBuffers(1, &indexBuffer);
	}

	texture.Cleanup();
	texture2.Cleanup();
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
	texture = Texture();
	texture.LoadTexture("../Assets/Textures/MetalFrameWood.jpg");

	texture2 = Texture();
	texture2.LoadTexture("../Assets/Textures/MetalFrame.jpg");

	vertexData = {
        /* Position */ /* Normals */ /* Texture Coords */
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f


	};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	/*indexData = {
		2, 0, 3, 2, 1, 0
	};
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);*/
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	texture.Cleanup();
	texture2.Cleanup();

	vertexBuffer = 0;
	indexBuffer = 0;
}

void Mesh::CalculateTransform()
{
    world = glm::translate(glm::mat4(1.0f), position);
    world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));
    world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));
    world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));
    world = glm::scale(world, scale);
}

void Mesh::Render(glm::mat4 _pv)
{
    glUseProgram(shader->GetProgramID());
    rotation.y = 0.005f;

    CalculateTransform();
    SetShaderVariables(_pv);
    BindAttributes();

    glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 8);
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
    shader->SetMat4("World", world);
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);

    shader->SetVec3("light.position", lightPosition);
    shader->SetVec3("light.direction", glm::normalize(glm::vec3({ 0, 0, 0 }) - lightPosition));
    shader->SetVec3("light.color", lightColor);
    shader->SetFloat("light.constant", 1.0f);
    shader->SetFloat("light.linear", 0.09f);
    shader->SetFloat("light.quadratic", 0.032f);
    shader->SetVec3("light.ambientColor", { 0.1f, 0.1f, 0.1f });
    shader->SetVec3("light.diffuseColor", { 1.0f, 1.0f, 1.0f });
    shader->SetVec3("light.specularColor", { 3.0f, 3.0f, 3.0f });
    shader->SetFloat("light.coneAngle", glm::radians(15.0f));
    shader->SetFloat("light.falloff", 100);

    shader->SetFloat("material.specularStrength", 8);
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, texture.GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, texture2.GetTexture());
}

void Mesh::BindAttributes()
{
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

#pragma region 3rd attribute buffer: normals
    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(shader->GetAttrNormals(),
        3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
#pragma endregion

    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(shader->GetAttrTexCoords(),
        2, GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
}
