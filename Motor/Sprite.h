#pragma once
#include <GL/glew.h>
using namespace std;
class Sprite
{
	float x, y;
	int width, height;
	float vertexData;
	GLuint vboID;
public:
	Sprite();
	~Sprite();
	void init(float, float, int, int);
	void draw();
};

