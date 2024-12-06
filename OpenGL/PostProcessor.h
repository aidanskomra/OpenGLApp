#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
	void Create(Shader* _postShader);
	void Cleanup();
	void Start();
	void End();

private:
	void CreateVertices();
	void CreateBuffers();
	void BindVertices();

private:
	GLuint frameBuffer = 0;
	GLuint textureColorBuffer = 0;
	GLuint renderBufferObject = 0;
	GLuint vertexBuffer = 0;
	Shader* postShader = nullptr;
};
#endif