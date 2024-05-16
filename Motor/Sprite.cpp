#include "Sprite.h"

Sprite::Sprite() : vboID(0) { }

Sprite::Sprite(float x, float y, int width, int height, string texturePath, bool isVisible) : vboID(0)
{
	init(x, y, width, height, texturePath, isVisible);
}

Sprite::~Sprite()
{
	if (vboID == 0) {
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::init(float x, float y, int width, int height, string texturePath, bool isVisible)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->isVisible = isVisible;

	if (vboID == 0) {
		// Genera un indentificador único de Vertex Buffer Object
		glGenBuffers(1, &vboID);
	}
	if (vboID == 0) {
		fatalError("No se pudo crear buffer");
	}

	texture = ResourceManager::getTexture(texturePath);
	Vertex vertexData[6] = {
		{
			x + width, y + height,
			255, 0, 0, 255,
			1.0f, 1.0f
		},
		{
			x, y + height,
			0, 0, 255, 255,
			0.0f, 1.0f
		},
		{
			x, y,
			255, 0, 0, 255,
			0.0f, 0.0f
		},
		{
			x, y,
			255, 0, 0, 255,
			0.0f, 0.0f
		},
		{
			x + width, y,
			0, 255, 0, 255,
			1.0f, 0.0f
		},
		{
			x + width, y + height,
			255, 0, 0, 255,
			1.0f, 1.0f
		}
	};
		
	/*
	Vertex vertexData[6];
	// Asignación de valores Position 2D a los datos de vertex
	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);
	
	// Asignación de valores RGBA a los datos de vertex(RAM)
	for (size_t i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 0, 255);
	}
	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	// Asignación de valores UV a los datos de vertex(RAM)
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);
	*/

	// Vincular buffer del sprite (GPU) con el vertex target (GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	
	// Asignar los datos de los vertices (RAM) como bytes al buffer vinculado al vertex target (GL_ARRAY_BUFFER)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	// Desvincular el buffer del vertex target (GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	// Asignar valor al atributo posición
	glVertexAttribPointer(
		VERTEX_ATTRIB_INDEX_POS,
		2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position)
	);
	// Asignar valor al atributo color
	glVertexAttribPointer(
		VERTEX_ATTRIB_INDEX_COLOR,
		4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(Vertex), (void*)offsetof(Vertex, color)
	);
	// Asignar valor al atributo UV
	glVertexAttribPointer(
		VERTEX_ATTRIB_INDEX_UV,
		2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, uv)
	);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	// Desvincular la textura del texture space target GL_TEXTURE_2D
	// Desvincular el buffer del buffer target GL_ARRAY_BUFFER
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
