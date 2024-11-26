#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardIncludes.h"

class Texture
{
public:
	virtual ~Texture();

	GLuint GetTexture() { return texture; }

	void LoadTexture(std::string _filename);
	void Cleanup();

private:
	int width = -1;
	int height = -1;
	int channels = -1;
	GLuint texture;
};

#endif