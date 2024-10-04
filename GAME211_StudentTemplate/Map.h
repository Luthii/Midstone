#pragma once

#include "GameManager.h"
#include "TextureManager.h"

class Map {
private:
	// Source, Destination
	SDL_Rect source, dest;

	// Using the discord textures
	SDL_Texture* floor;
	SDL_Texture* wallTop;
	SDL_Texture* wallBott;

	int map[18][31];

protected:
	class GameManager* game;

public:

	Map(GameManager* game);
	~Map();

	void LoadMap(int arr[18][31]);
	void DrawMap();
};