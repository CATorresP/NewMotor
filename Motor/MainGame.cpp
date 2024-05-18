#include "MainGame.h"

MainGame::MainGame()
	: width(800), height(600), window(nullptr), gameState(GameState::PLAY)
{
	camera.init(width, height);
}

MainGame::~MainGame() { }

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
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(event.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(event.key.keysym.sym);
			break;
		}
	}
}

void MainGame::handleInput()
{
	if (inputManager.isKeyPressed(SDLK_w)) {
		//cout << "Estoy presionando arriba\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
	}
	if (inputManager.isKeyPressed(SDLK_s)) {
		//cout << "Estoy presionando abajo\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
	}
	if (inputManager.isKeyPressed(SDLK_a)) {
		//cout << "Estoy presionando izquierda\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
	}
	if (inputManager.isKeyPressed(SDLK_d)) {
		//cout << "Estoy presionando derecha\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
	}
	if (inputManager.isKeyPressed(SDLK_q)) {
		cout << "Estoy presionando zoom in\n";
	}
	if (inputManager.isKeyPressed(SDLK_e)) {
		cout << "Estoy presionando zoom out\n";
	}
}

void MainGame::initShaders()
{
	program.init();
	program.compileShaders(
		"Shaders/ColorShaderVert2.txt", "Shaders/ColorShaderFrag2.txt");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.addAttribute("vertexUV");
	program.linkShader();
}

void MainGame::run()
{
	init();
	sprites.emplace_back(-1, -1, 1, 1, "Images/mario64.png");
	sprites.emplace_back(0, -1, 1, 1, "Images/mario64.png");
	/*
	imagePathPull.push_back("Images/mario64.png");
	imagePathPull.push_back("Images/mariokart64.png");
	imagePathPull.push_back("Images/mariokartDS.png");
	imagePathPull.push_back("Images/Super_Mario_Galaxy.png");
	imagePathPull.push_back("Images/Super_Paper_Mario.png");
	imagePathPull.push_back("Images/Super_Smash_Bros_Brawl.png");
	*/
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocationID = program.getUniformLocation("time");
	glUniform1f(timeLocationID, time);
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 2);
	/*
	if (ticks % 10000 == 0) {
		sprites.emplace_back(
			float(rand() % 100) / 100 - 1, float(rand() % 100) / 100 - 1,
			1, 1,
			imagePathPull[rand() % imagePathPull.size()]
		);
	}
	*/
	for (auto it : sprites) {
		if (it.isVisible) {
			it.draw();
		}
	}
	time += 0.000002;
	//glm::mat4 cameraMatrix = camera.getCameraMatrix();
	//GLuint pLocation = program.getUniformLocation("P");
	//glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	// ticks++;
	program.unuse();
	window->swapWindow();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
		camera.update();
	}
}
