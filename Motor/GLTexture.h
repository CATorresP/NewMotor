#pragma once
#include <GL/glew.h>

enum TextureWrapMode {
	fit_sprite,
	fill_sprite,
	resize_sprite,
	original_sprite
};

struct GLTexture {
	GLuint id;
	float width, height;
};