#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include <string>

enum class TEXTURE2D_ERROR
{
	TEX_OK,
	TEX_LOAD_FAIL
};

class Texture2D
{
private:
	unsigned int m_texID;
	int m_width;
	int m_height;
	int m_nrChannels;

private:
	void Init();

public:
	Texture2D();
	~Texture2D();
	void Bind() const;
	void Unbind() const;
	TEXTURE2D_ERROR LoadImage(std::string);
};