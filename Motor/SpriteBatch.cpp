#include "SpriteBatch.h"

RenderBatch::RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) 
{
}

RenderBatch::~RenderBatch()
{
}

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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, uv));

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void SpriteBatch::createRenderBatches()
{
	vector<Vertex> vertices;
	vertices.resize(glyphs.size() * 6);
	if (glyphs.empty())
		return;
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
	for (size_t i = 1; i < glyphs.size(); i++)
	{
		if (glyphs[i]->texture != glyphs[i - 1]->texture) {
			renderBatches.emplace_back(offset, 6, glyphs[i]->texture);
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
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
	this->sortType = sortType;
	renderBatches.clear();
	// puede haber un error
	for (Glyph* it : glyphs) {
		delete it;
	}
}

void SpriteBatch::end()
{
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4 uvRect, GLuint texture, float depth, Color& color)
{
	Glyph* glyph = new Glyph();
	glyph->texture = texture;
	glyph->depth = depth;
	// En este caos especifico se usa w como distancia más que como valor dimensional
	glyph->topLeft.color = color;
	glyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	glyph->bottomLeft.color = color;
	glyph->bottomLeft.setPosition(destRect.x, destRect.y);
	glyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	glyph->bottomRight.color = color;
	glyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	glyph->bottomRight.setUV(uvRect.x + destRect.z, uvRect.y);

	glyph->topRight.color = color;
	glyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + uvRect.w);
	glyph->topRight.setUV(uvRect.x + destRect.z, uvRect.y + uvRect.w);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(vba);
	for (size_t i = 0; i < renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::sortGlyph()
{
	switch (sortType)
	{
	case GlyphSortType::NONE:
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(glyphs.begin(), glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return (a->texture < b->texture);
}
