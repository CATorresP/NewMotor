#pragma once
#include "Sprite.h"
#include "SDL/SDL.h"
#include "GL/eglew.h"
#include <iostream>
#include "Window.h"
#include "GLS_Program.h"
#include <vector>
#include <cstdlib>
#include "Camera2D.h"
#include "InputManager.h"
using namespace std;
enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
	InputManager inputManager;
	vector<Sprite> sprites;
	int width, height;
	Window* window;
	Camera2D camera;
	const float CAMERA_SPEED = 0.05f;
	const float CAMERA_SCALE = 0.1f;
	GLS_Program program;
	float time = 0;
	//size_t ticks = 0;
	//vector<string> imagePathPull;
public:
	GameState gameState;
private:
	void init();
	void processInput();
	void handleInput();
	void initShaders();
public:
	MainGame();
	~MainGame();
	void run();
	void draw();
	void update();
};

