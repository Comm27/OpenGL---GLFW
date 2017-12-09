#pragma once
#include <glad/glad.h>
#include <iostream>

enum class BUFFER_USAGE
{
	STATIC,
	DYNAMIC,
};

enum class BUFFER_TYPE
{
	ARRAY,
	ELEMENT_ARRAY,
	NONE
};

class Buffer
{
private:
	GLuint m_buffID;
	GLenum bufferType;

private:
	void Init(BUFFER_TYPE);
	GLenum GetUsageType(BUFFER_USAGE);
public:
	Buffer(BUFFER_TYPE);
	~Buffer();
	void Bind() const;
	void Unbind() const;
	void FeedData(const void *, BUFFER_USAGE usage = BUFFER_USAGE::STATIC);
	void RemoveBuffer();
};