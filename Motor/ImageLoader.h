#pragma once
#include "GLTexture.h"
#include <string>
#include "picoPNG.h"
#include "Error.h"
#include "IOManager.h"
using namespace std;
class ImageLoader
{
public:
	static GLTexture loadPng(string filePath);
};

