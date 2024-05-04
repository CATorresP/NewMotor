#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <fstream>
#include "Error.h"
using namespace std;

class GLS_Program
{
private:
	GLuint programID, vertexShaderID, fragmentShaderID;
	int numAttribute;
	void compileShader(const string& shaderPath, GLuint id);
public:
	GLS_Program();
	~GLS_Program();
	void compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
	void linkShader();
	void addAttribute(const string attributeName);
	void use();
	void unuse();
	GLuint getUniformLocation(const string& name);
};

