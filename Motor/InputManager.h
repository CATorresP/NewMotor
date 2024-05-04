#pragma once
#include "glm/glm.hpp"
#include <unordered_map>
using namespace std;
class InputManager
{
private:
	unordered_map<unsigned int, bool> keys;
	glm::vec2 mouseCoords;
public:
	InputManager();
	~InputManager();
	glm::vec2 getMouseCoords()const {
		return mouseCoords;
	}
	void setMouseCoords(float, float);
	void pressKey(unsigned int keyCode);
	void releaseKey(unsigned int keyCode);
	bool isKeyPressed(unsigned int keyCode);
};

