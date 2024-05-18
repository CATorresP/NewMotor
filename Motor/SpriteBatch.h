#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
using namespace std;
/*
enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

//SpriteBatch
struct Glyph
{
public:
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint offset, GLuint numVertices, GLuint texture);
	~RenderBatch();
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch {
	GLuint vbo;
	GLuint vba;
	vector<RenderBatch> renderBatches;
	vector<Glyph*> glyphs;
	void createVertexArray();
	GlyphSortType sortType;
	void createRenderBatches();
public:
	SpriteBatch();
	~SpriteBatch();
	void init();
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4 uvRect, float depth, Color& color);
	void renderBatch();
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);
};
*/