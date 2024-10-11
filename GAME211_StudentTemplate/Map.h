#pragma once
#include "TextureManager.h"
#include "SDL.h"

class Map {
private:
	// Source, Destination
	SDL_Rect source, dest;

	// Using the discord textures
	SDL_Texture* floor;
	SDL_Texture* wallTop;
	SDL_Texture* wallBott;

	SDL_Renderer* renderer;

	int map[18][31];

public:

	Map(SDL_Renderer* _renderer);
	~Map();

	void LoadMap(int arr[18][31]);
	void DrawMap();
};