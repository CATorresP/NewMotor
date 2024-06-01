#include "MainGame.h"

MainGame::MainGame() : window(nullptr), width(800), height(600), gameState(GameState::PLAY)
{
	camera.init(width, height);
}

MainGame::~MainGame()
{
}

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
	handleInput();
}

void MainGame::handleInput()
{
	if (inputManager.isKeyPressed(SDLK_w)) {
		//cout << "estoy presionando arriba\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
	}
	if (inputManager.isKeyPressed(SDLK_s)) {
		//cout << "estoy presionando abajo\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
	}
	if (inputManager.isKeyPressed(SDLK_a)) {
		cout << "estoy presionando izquierda\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
	}
	if (inputManager.isKeyPressed(SDLK_d)) {
		cout << "estoy presionando derecha\n";
		camera.setPosition(
			camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
	}
	if (inputManager.isKeyPressed(SDLK_q)) {
		cout << "estoy presionando zoom in\n";
	}
	if (inputManager.isKeyPressed(SDLK_e)) {
		cout << "estoy presionando zoom out\n";
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

void MainGame::run()
{
	init();
	sprites.emplace_back();
	sprites.back().init(-1, -1, 1, 1, "Images/mario64.png");
	sprites.emplace_back();
	sprites.back().init(0, -1, 1, 1, "Images/mariokartDS.png");
	/*
	sprite.init(-1,-1,1,1);
	float x, y;
	x = float(rand() % 10) / 10 - 1;
	y = float(rand() % 10) / 10 - 1;

	imagePathPull.push_back("Images/mario64.png");
	imagePathPull.push_back("Images/mariokart64.png");
	imagePathPull.push_back("Images/mariokartDS.png");
	imagePathPull.push_back("Images/Super_Mario_Galaxy.png");
	imagePathPull.push_back("Images/Super_Paper_Mario.png");
	imagePathPull.push_back("Images/Super_Smash_Bros_Brawl.png");
	*/
	camera.init(width, height);
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
	// glUniform1i(imageLocation, 2);

	/*
	if (ticks % 10000 == 0) {
		Sprite newSprite;
		size_t i_image = rand() % imagePathPull.size();
		newSprite.init(
			float(rand() % 100) / 100 - 1,
			float(rand() % 100) / 100 - 1, 
			1, 1, 
			imagePathPull[i_image]);
		sprites.push_back(newSprite);
	}
	ticks++;
	*/
	for (auto it : sprites) {
		it.draw();
	}
	time += 0.0002;
	glm::mat4 cameraMatrix = camera.getCameraMatrix();
	GLuint pLocation = program.getUniformLocation("P");
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
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
