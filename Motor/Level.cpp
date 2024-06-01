#include "Level.h"

void Level::parseLevel()
{
	spritebatch.init();
	spritebatch.begin();
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color;
	color.set(255, 255, 255, 255);
	for (string row : levelData) {
		for (char e : row) {

		}
	}
}

Level::Level(const string& fileName)
{
	ifstream file;
	file.open(fileName);
	if (file.fail()) {
		fatalError("Fallo el archivo " + fileName);
	}
	string tmp;
	file >> tmp >> numHumans;
	getline(file, tmp);
	while (getline(file, tmp)) {
		levelData.push_back(tmp);
	}
	file.close();
}

Level::~Level()
{
}

void Level::draw()
{
}
