#pragma once
#include "GLTexture.h"
#include <map>
#include <string>
#include "ImageLoader.h"
using namespace std;
class TextureCache
{
private:
	map<string, GLTexture> textureMap;
public:
	TextureCache();
	~TextureCache();
	GLTexture getTexture(string texturePath);
};

