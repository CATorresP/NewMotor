#pragma once
#include <GL/glew.h>
#include <cstddef>
#include "Vertex.h"
#include "GLTexture.h"
#include <string>
#include "ResourceManager.h"
using namespace std;
class Sprite
{
	float x, y;
	int width, height;
	float vertexData;
	GLuint vboID;
	GLTexture texture;
public:
	Sprite();
	~Sprite();
	void init(float, float, int, int, string);
	void draw();
};

