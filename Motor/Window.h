#pragma once
#include "SDL/SDL.h"
#include "GL/eglew.h"
#include <string>
#include "Error.h"
using namespace std;

enum WindowFlags {
	INVISIBLE = 0X1,
	FULLSCREEN = 0X2,
	BORDERLESS = 0X4
};

class Window
{
	SDL_Window* window;
	int screenWidth;
	int screenHeight;

public:
	Window();
	~Window();
	int create(string, int, int, int);
	void swapWindow();
	int getScreenWidth();
	int getScreenHeight();
};

