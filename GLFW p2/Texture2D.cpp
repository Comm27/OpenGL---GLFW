#include "Texture2D.h"

void Texture2D::Init()
{
	glGenTextures(1, &m_texID);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Unbind();
}

Texture2D::Texture2D()
{
	stbi_set_flip_vertically_on_load(true);
	Init();
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texID);
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texID);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

TEXTURE2D_ERROR Texture2D::LoadImage(std::string imagePath)
{
	std::string imgFormatStr = imagePath.substr(imagePath.find_last_of('.') + 1);
	GLenum imageFormat = GL_RGB;

	unsigned char *data = stbi_load(imagePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);

	if (!data)
	{
		return TEXTURE2D_ERROR::TEX_LOAD_FAIL;
	}

	Bind();

	if (imgFormatStr.compare("png") == 0)
	{
		imageFormat = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();
	stbi_image_free(data);

	return TEXTURE2D_ERROR::TEX_OK;
}