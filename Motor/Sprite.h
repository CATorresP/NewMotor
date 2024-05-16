#pragma once
#include <GL/glew.h>
#include <cstddef>
#include "Vertex.h"
#include "GLTexture.h"
#include <string>
#include "ResourceManager.h"

#define VERTEX_ATTRIB_INDEX_POS 0
#define VERTEX_ATTRIB_INDEX_COLOR 1
#define VERTEX_ATTRIB_INDEX_UV 2

using namespace std;

class Sprite
{
	float x, y;
	int width, height;
	GLuint vboID;
	GLTexture texture;
public:
	bool isVisible;
public:
	Sprite();
	Sprite(float x, float y, int width, int height, string texturePath = "Images/no_image.png", bool isVisible = true);
	~Sprite();
	void init(float x, float y, int width, int height, string texturePath, bool isVisible);
	void draw();
};

