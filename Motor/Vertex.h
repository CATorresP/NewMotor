#pragma once
#include <GL/glew.h>

struct Position {
	float x, y;
	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}
};
struct Color {
	GLubyte r, g, b, a;
	void set(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};
struct UV {
	float u, v;
	void set(float u, float v) {
		this->u = u;
		this->v = v;
	}
};
struct Vertex {
	Position position;
	Color color;
	UV uv;
	void setUV(float u, float v) {
		position.set(u, v);
	}
	void setPosition(float x, float y) {
		position.set(x, y);
	}
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.set(r, g, b, a);
	}
};
