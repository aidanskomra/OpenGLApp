#include "Mesh.h"
#include "Shader.h"
#include "GameController.h"
#include <OBJ_Loader.h>

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

	textureDiffuse.Cleanup();
	textureSpecular.Cleanup();
}

void Mesh::Create(Shader* _shader, std::string _file)
{
    shader = _shader;

    #pragma region Mesh Loading
    objl::Loader loader;
    M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh");

    for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
    {
        objl::Mesh curMesh = loader.LoadedMeshes[i];
        std::vector<objl::Vector3> tangents;
        std::vector<objl::Vector3> bitangents;
        std::vector<objl::Vertex> triangle;
        objl::Vector3 tangent;
        objl::Vector3 bitangent;
        for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
        {
            triangle.clear();
            triangle.push_back(curMesh.Vertices[j]);
            triangle.push_back(curMesh.Vertices[j + 1]);
            triangle.push_back(curMesh.Vertices[j + 2]);
            CalculateTangents(triangle, tangent, bitangent);
            tangents.push_back(tangent);
            bitangents.push_back(bitangent);
        }
        for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
        {
            vertexData.push_back(curMesh.Vertices[j].Position.X);
            vertexData.push_back(curMesh.Vertices[j].Position.Y);
            vertexData.push_back(curMesh.Vertices[j].Position.Z);
            vertexData.push_back(curMesh.Vertices[j].Normal.X);
            vertexData.push_back(curMesh.Vertices[j].Normal.Y);
            vertexData.push_back(curMesh.Vertices[j].Normal.Z);
            vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
            vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);

            if (loader.LoadedMaterials[0].map_bump != "")
            {
                int index = j / 3;
                vertexData.push_back(tangents[index].X);
                vertexData.push_back(tangents[index].Y);
                vertexData.push_back(tangents[index].Z);
                vertexData.push_back(bitangents[index].X);
                vertexData.push_back(bitangents[index].Y);
                vertexData.push_back(bitangents[index].Z);
            }
        }
    }

    std::string diffuseMap = loader.LoadedMaterials[0].map_Kd;
    const size_t last_slash_idx = diffuseMap.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        diffuseMap.erase(0, last_slash_idx + 1);
    }

#pragma region Texture Loading
    textureDiffuse = Texture();
    if (loader.LoadedMaterials[0].map_Kd != "")
    {
        textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));
    }
    else
    {
        textureDiffuse.LoadTexture("../Assets/Textures/Pattern.png");
    }

    textureSpecular = Texture();
    if (loader.LoadedMaterials[0].map_Ks != "")
    {
        textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Ks));
    }

    textureNormal = Texture();
    if (loader.LoadedMaterials[0].map_bump != "")
    {
        enableNormalMaps = true;
        textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_bump));
    }
#pragma endregion

    vertexStride = 8;
    if (enableNormalMaps)
    {
        vertexStride += 6;
    }

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	textureDiffuse.Cleanup();
	textureSpecular.Cleanup();

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

    glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / vertexStride);
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
    shader->SetMat4("World", world);
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);
    shader->SetInt("EnableNormalMaps", enableNormalMaps);

    std::vector<Mesh*>& lights = GameController::GetInstance().GetLights();
    for (int i = 0; i < lights.size(); i++)
    {
        shader->SetVec3(Concat("light[", i, "].position").c_str(), lights[i]->GetPosition());
        shader->SetVec3(Concat("light[", i, "].direction").c_str(), lights[i]->GetLightDirection());

        shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
        shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), lights[i]->GetColor());
        shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

        shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
        shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
        shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

        shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
        shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
    }

    shader->SetFloat("material.specularStrength", 8);
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, textureDiffuse.GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, textureSpecular.GetTexture());
    shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, textureNormal.GetTexture());
}

void Mesh::BindAttributes()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        vertexStride * sizeof(float),
        (void*)0
    );
   

#pragma region 3rd attribute buffer: normals
    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(shader->GetAttrNormals(),
        3, GL_FLOAT, GL_FALSE,
        vertexStride * sizeof(float),
        (void*)(3 * sizeof(float))
    );
#pragma endregion

    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(shader->GetAttrTexCoords(),
        2, GL_FLOAT, GL_FALSE,
        vertexStride * sizeof(float),
        (void*)(6 * sizeof(float))
    );

#pragma region BindNormalMapData
    if (enableNormalMaps)
    {
        // 4th attribute buffer: tangent
        glEnableVertexAttribArray(shader->GetAttrTangents());
        glVertexAttribPointer(shader->GetAttrTangents(), // the attribute we want to configure
            3, GL_FLOAT, GL_FALSE,          //size, type, normalized?,
            vertexStride * sizeof(float),   // stride floats per vertex definition
            (void*)(8 * sizeof(float))); // array buffer offset

        // 5th attribute buffer: tangent
        glEnableVertexAttribArray(shader->GetAttrBitangents());
        glVertexAttribPointer(shader->GetAttrBitangents(), // the attribute we want to configure
            3, GL_FLOAT, GL_FALSE,          //size, type, normalized?,
            vertexStride * sizeof(float),   // stride floats per vertex definition
            (void*)(11 * sizeof(float))); // array buffer offset

    }
#pragma endregion
}

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
    std::string index = std::to_string(_index);
    return (_s1 + index + _s2);
}

std::string Mesh::RemoveFolder(std::string& _map)
{
    const size_t last_slash_idx = _map.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        _map.erase(0, last_slash_idx + 1);
    }
    return _map;
}

void Mesh::CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
    // calculate tangent/bitangent vectors of both triangles
    objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
    objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
    objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
    objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

    float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

    _tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
    _tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
    _tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

    _bitangent.X = f * (-deltaUV2.X * edge1.X - deltaUV1.X * edge2.X);
    _bitangent.Y = f * (-deltaUV2.X * edge1.Y - deltaUV1.X * edge2.Y);
    _bitangent.Z = f * (-deltaUV2.X * edge1.Z - deltaUV1.X * edge2.Z);
}
