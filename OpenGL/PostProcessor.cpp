#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"

void PostProcessor::Create(Shader* _postShader)
{
	postShader = _postShader;
	CreateBuffers();
	CreateVertices();
}

void PostProcessor::Cleanup()
{
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteTextures(1, &textureColorBuffer);
	glDeleteRenderbuffers(1, &renderBufferObject);
}

void PostProcessor::CreateBuffers()
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	Resolution r = WindowController::GetInstance().GetResolution();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.width, r.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.width, r.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::CreateVertices()
{
	float vertexData[] = {
		-1.0f, 1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		1.0f, -1.0f,	1.0f, 0.0f,

		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		1.0f, 1.0f,		1.0f, 1.0f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(postShader->GetAttrVertices());
	glVertexAttribPointer(postShader->GetAttrVertices(),
		2,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(float),
		(void*)0);

	glEnableVertexAttribArray(postShader->GetAttrTexCoords());
	glVertexAttribPointer(postShader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(float),
		(void*)(2 * sizeof(float)));
}

void PostProcessor::Start()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(postShader->GetProgramID());
	postShader->SetTextureSampler("screenTexture", GL_TEXTURE0, 0, textureColorBuffer);
	BindVertices();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(postShader->GetAttrVertices());
	glDisableVertexAttribArray(postShader->GetAttrTexCoords());
}