#include "MainGame.h"

void MainGame::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fatalError("Error al iniciar SDL.");
	}
	window = new Window();
	window->create("Motor WD2M", width, height, 0);
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << 
				"Posición en X " << event.motion.x << 
				" posición en y " << event.motion.y << endl;
			break;
		}
	}
}

MainGame::MainGame()
{
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	init();
	sprite.init(-1,-1,-1,-1);
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sprite.draw();
	//SDL_GL_SwapWindow(window);
	window->swapWindow();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}
