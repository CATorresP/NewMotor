#include "SpriteBatch.h"
/*
void SpriteBatch::createVertexArray()
{
	if (vba == 0) {
		glGenVertexArrays(1, &vba);
	}
	glBindVertexArray(vba);
	if (vbo == 0) {
		glGenBuffers(1, &vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		0, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position)
	);
	glVertexAttribPointer(
		1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(Vertex), (void*)offsetof(Vertex, color)
	);
	glVertexAttribPointer(
		2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, uv)
	);
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	vector<Vertex> vertices;
	vertices.resize(glyphs.size() * 6);
	if (glyphs.empty()) {
		return;
	}
	int cv = 0;
	int offset = 0;
	renderBatches.emplace_back(offset, 6, glyphs[0]->texture);
	vertices[cv++] = glyphs[0]->topLeft;
	vertices[cv++] = glyphs[0]->bottomLeft;
	vertices[cv++] = glyphs[0]->bottomRight;
	vertices[cv++] = glyphs[0]->bottomRight;
	vertices[cv++] = glyphs[0]->topRight;
	vertices[cv++] = glyphs[0]->topLeft;
	offset += 6;
	for (size_t i = 0; i < glyphs.size(); i++)
	{
		if (glyphs[i]->texture != glyphs[i - 1]->texture) {
			renderBatches.emplace_back(offset, 6, glyphs[i]);
		}
		else {
			renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = glyphs[i]->topLeft;
		vertices[cv++] = glyphs[i]->bottomLeft;
		vertices[cv++] = glyphs[i]->bottomRight;
		vertices[cv++] = glyphs[i]->bottomRight;
		vertices[cv++] = glyphs[i]->topRight;
		vertices[cv++] = glyphs[i]->topLeft;

	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 
		vertices.size() * sizeof(Vertex), 
		nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 
		vertices.size() * sizeof(Vertex), 
		vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteBatch::SpriteBatch() : vbo(0), vba(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType)
{
}

void SpriteBatch::end()
{
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4 uvRect, float depth, Color& color)
{
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(vba);
	for (size_t i = 0; i < renderBatches.size(); i++) 
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset,
			renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return false;
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return false;
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return false;
}

RenderBatch::RenderBatch(GLuint offset, GLuint numVertices, GLuint texture)
{
}

RenderBatch::~RenderBatch()
{
}
*/