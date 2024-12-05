#include "Skybox.h"
#include "Shader.h"
#include "OBJ_Loader.h"

Skybox::~Skybox()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
	texture.Cleanup();
}

void Skybox::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	vertexBuffer = 0;
	
	texture.Cleanup();
}

void Skybox::Create(Shader* _shader, std::string _file, std::vector<std::string> _faces)
{
	shader = _shader;

	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh.");

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			vertexData.push_back(curMesh.Vertices[j].Position.X);
			vertexData.push_back(curMesh.Vertices[j].Position.Y);
			vertexData.push_back(curMesh.Vertices[j].Position.Z);
		}
	}

	texture = Texture();
	texture.LoadCubemap(_faces);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}

void Skybox::SetShaderVariables(glm::mat4 _pv)
{
	shader->SetMat4("PV", _pv);
	shader->SetTextureSampler("skyboxTexture", GL_TEXTURE_CUBE_MAP, 0, texture.GetTexture());
}

void Skybox::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind the vertex buffer

	// attribute buffer : vertices
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(shader->GetAttrVertices(), // The attribute we want to configure
		3,					// size (3 components)
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		3 * sizeof(float),	// stride (3 floats per vertex definition)
		(void*)0);			// array buffer offset
}

void Skybox::Render(glm::mat4 _pv)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(shader->GetProgramID());	// Use our shader
	SetShaderVariables(_pv);
	BindAttributes();
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
	glDisableVertexAttribArray(shader->GetAttrNormals());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}