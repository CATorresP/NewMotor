#pragma once
#include <string>
#include <vector>
#include "SpriteBatch.h"
#include <fstream>
#include "ResourceManager.h"
#include "Error.h"
using namespace std;
const int TILE_WIDTH = 64;
class Level
{
	vector<string> levelData;
	int numHumans;
	void parseLevel();
	glm::vec2 playerPosition;
	vector<glm::vec2> zombies;
public:
	SpriteBatch spritebatch;
public:
	Level(const string& fileName);
	~Level();
	void draw();
	int getNumHumans() {
		return numHumans;
	}
	glm::vec2 getPlayerPosition()const {
		return playerPosition;
	}
	const vector<glm::vec2> getZombiesPosition() {
		return zombies;
	}
	const vector<string>& getLevelData() {
		return levelData;
	}
	int getWidth()const {
		return levelData[0].size();
	}
	int getHight()const {
		return levelData.size();
	}
};

