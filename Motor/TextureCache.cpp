#include "TextureCache.h"

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath)
{
	auto mit = textureMap.find(texturePath);
	if (mit == textureMap.end()) {
		GLTexture texture = ImageLoader::loadPng(texturePath);
		//pair<string, GLTexture> newPair(texturePath, texture);
		//textureMap.insert(newPair);

		textureMap[texturePath] = texture;
		return texture;
	}
	return mit->second;
}
