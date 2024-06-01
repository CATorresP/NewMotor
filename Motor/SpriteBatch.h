#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include <algorithm>

using namespace std;
enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};
struct Glyph {
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};
class RenderBatch {
public:
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
public:
	RenderBatch(GLuint offset, GLuint numVertices, GLuint texture);
	~RenderBatch();
};
class SpriteBatch
{
	GLuint vbo;
	GLuint vba;
	vector<Glyph*> glyphs;
	vector<RenderBatch> renderBatches;
	GlyphSortType sortType;
	void createVertexArray();
	void createRenderBatches();
public:
	SpriteBatch();
	~SpriteBatch();
	void init();
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4 uvRect, GLuint texture, float depth, Color& color);
	void renderBatch();
	void sortGlyph();
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);
};

