#pragma once
#include <glad\glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Shader
{
private:
	GLuint m_program;

public:
	Shader(const std::string &vFilePath, const std::string &fFilePath);
	~Shader();
	void Use() const;

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetFloatV(const std::string &name, const GLfloat *arr) const;
};