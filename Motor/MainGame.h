#pragma once
#include "Sprite.h"
#include "SDL/SDL.h"
#include "GL/eglew.h"
#include <iostream>
#include "Window.h"
using namespace std;
enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
	Sprite sprite;
	int width, height;
	//SDL_Window* window;
	Window* window;
public:
	GameState gameState;
private:
	void init();
	void processInput();
public:
	MainGame();
	~MainGame();
	void run();
	void draw();
	void update();
};

