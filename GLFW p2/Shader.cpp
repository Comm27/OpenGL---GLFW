#include "Shader.h"

Shader::Shader(const std::string &vFilePath, const std::string &fFilePath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vFilePath);
		fShaderFile.open(fFilePath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::Shader::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char *vShaderSourceCode = vertexCode.c_str();
	const char *fShaderSourceCode = fragmentCode.c_str();

	int vertexShader, fragmentShader;
	int success;
	int length;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vShaderSourceCode, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		char *infoLog = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(vertexShader, length, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(fragmentShader, 1, &fShaderSourceCode, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		char *infoLog = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(fragmentShader, length, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	glValidateProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		char *infoLog = (char*)alloca(sizeof(char) * length);
		glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::Use() const
{
	glUseProgram(m_program);
}

void Shader::SetBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::SetInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::SetFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::SetFloatV(const std::string & name, const GLfloat * arr) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, arr);
}
