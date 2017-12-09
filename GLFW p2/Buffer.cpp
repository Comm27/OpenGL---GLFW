#include "Buffer.h"

void Buffer::Init(BUFFER_TYPE type)
{
	glGenBuffers(1, &m_buffID);

	switch (type)
	{
	case BUFFER_TYPE::ARRAY:
		bufferType = GL_ARRAY_BUFFER;
		break;

	case BUFFER_TYPE::ELEMENT_ARRAY:
		bufferType = GL_ELEMENT_ARRAY_BUFFER;
		break;

	default:
		break;
	}
}

GLenum Buffer::GetUsageType(BUFFER_USAGE buffUsage)
{
	GLenum usageType;

	switch (buffUsage)
	{
	case BUFFER_USAGE::STATIC:
		usageType = GL_STATIC_DRAW;
		break;

	case BUFFER_USAGE::DYNAMIC:
		usageType = GL_DYNAMIC_DRAW;
		break;

	default:
		break;
	}

	return usageType;
}

Buffer::Buffer(BUFFER_TYPE type)
{
	Init(type);
}

Buffer::~Buffer()
{
	RemoveBuffer();
}

void Buffer::Bind() const
{
	glBindBuffer(bufferType, m_buffID);
}

void Buffer::Unbind() const
{
	glBindBuffer(bufferType, 0);
}

void Buffer::FeedData(const void *data, BUFFER_USAGE usage)
{
	Bind();

	GLenum buffUsage = GetUsageType(usage);
	glBufferData(bufferType, sizeof(data), data, buffUsage);

	//Unbind();
}

void Buffer::RemoveBuffer()
{
	glDeleteBuffers(1, &m_buffID);
}