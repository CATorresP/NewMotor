#include "GLS_Program.h"

GLS_Program::GLS_Program() : programID(0), vertexShaderID(0), fragmentShaderID(0), numAttribute(0) { }

GLS_Program::~GLS_Program() { }

void GLS_Program::init() {
	programID = glCreateProgram();
	if (programID == 0) {
		fatalError("No se pudo crear el objeto Program.");
	}
}

void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	//vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	vertexShaderID = compileShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	fragmentShaderID = compileShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
}

//GLuint GLS_Program::compileShader(const string& shaderPath, GLuint id)
GLuint GLS_Program::compileShader(const string& shaderPath, GLenum shaderType)
{
	GLuint shaderID = glCreateShader(GL_VERTEX_SHADER);
	if (shaderID == 0) {
		fatalError("No se pudo generar el objeto shader para" + shaderPath);
	}
	string fileContent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("El archivo " + shaderPath + " no se encuentra disponible.");
	}
	while (getline(shaderFile, line)) {
		fileContent += line + "\n";
	}
	shaderFile.close();
	const char* contents = fileContent.c_str();
	glShaderSource(shaderID, 1, &contents, nullptr);
	glCompileShader(shaderID);
	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderID);
		fatalError("Shader no compilo " + printf("%s", &(errorLog[0])));
		return 0;
	}
	else {
		return shaderID;
	}
}

void GLS_Program::linkShader()
{

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		fatalError("Shader no linkearon " + printf("%s", &(infoLog[0])));
		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLS_Program::addAttribute(const string attributeName)
{
	glBindAttribLocation(programID, numAttribute++, attributeName.c_str());
}

void GLS_Program::use()
{
	glUseProgram(programID);
	for (size_t i = 0; i < numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::unuse()
{
	glUseProgram(0);
	for (size_t i = 0; i < numAttribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLuint GLS_Program::getUniformLocation(const string& name)
{
	GLuint location = glGetUniformLocation(programID, name.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Varaible uniform " + name + " no encontrada.");
	}
	return location;
}
