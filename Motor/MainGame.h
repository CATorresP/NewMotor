#pragma once
#include "Sprite.h"
#include "SDL/SDL.h"
#include "GL/eglew.h"
#include <iostream>
#include "Window.h"
#include "GLS_Program.h"
#include <vector>
#include <cstdlib>

using namespace std;
enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
	vector<Sprite> sprites;
	//Sprite sprite;
	int width, height;
	//SDL_Window* window;
	Window* window;
	GLS_Program program;
	float time = 0;
	size_t ticks = 0;
	vector<string> imagePathPull;
public:
	GameState gameState;
private:
	void init();
	void processInput();
	void initShaders();
public:
	MainGame();
	~MainGame();
	void run();
	void draw();
	void update();
};

