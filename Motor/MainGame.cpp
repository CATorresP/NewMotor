#include "MainGame.h"

void MainGame::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fatalError("Error al iniciar SDL.");
	}
	window = new Window();
	window->create("Motor WD2M", width, height, 0);
	initShaders();
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

void MainGame::initShaders()
{
	program.compileShaders("Shaders/ColorShaderVert.txt", "Shaders/ColorShaderFrag.txt");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.addAttribute("vertexUV");
	program.linkShader();
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
	//sprite.init(-1,-1,1,1);
	float x, y;
	x = float(rand() % 10) / 10 - 1;
	y = float(rand() % 10) / 10 - 1;
	sprite.init(x, y, 1, 1, "Images/mario64.png");

	imagePathPull.push_back("Images/mario64.png");
	imagePathPull.push_back("Images/mariokart64.png");
	imagePathPull.push_back("Images/mariokartDS.png");
	imagePathPull.push_back("Images/Super_Mario_Galaxy.png");
	imagePathPull.push_back("Images/Super_Paper_Mario.png");
	imagePathPull.push_back("Images/Super_Smash_Bros_Brawl.png");

	for (int i = 0; i < 6; ++i) {
	}
	for (auto it : sprites) {

	}
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocationID = program.getUniformLocation("time");
	glUniform1f(timeLocationID, time);
	if (int(time * 50000) % 10000 == 0) {
		Sprite newSprite;
		size_t i_image = rand() % imagePathPull.size();
		newSprite.init(
			float(rand() % 10) / 10 - 1,
			float(rand() % 10) / 10 - 1, 
			1, 1, 
			imagePathPull[i_image]);
		sprites.push_back(newSprite);
	}
	sprite.draw();
	for (auto it : sprites) {
		it.draw();
	}
	time += 0.0002;
	program.unuse();
	window->swapWindow();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}
