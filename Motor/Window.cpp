#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
}

int Window::create(string windowName, int screenWidth, int screenHeight, int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}
	window = SDL_CreateWindow(windowName.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenWidth, screenHeight,
		flags
	);
	if (window == nullptr) {
		fatalError("No se puede inicializar ventana.");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("No se puede inicializar glew.");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearDepth(1.0f);
	return 0;
}

void Window::swapWindow()
{
	SDL_GL_SwapWindow(window);
}

int Window::getScreenWidth()
{
	return screenWidth;
}

int Window::getScreenHeight()
{
	return screenHeight;
}