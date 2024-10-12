#pragma once
#include "TextureManager.h"
#include "SDL.h"

class Map {
private:
	// Source, Destination
	SDL_Rect source, dest;

	// tile textures
	SDL_Texture* floor;
	SDL_Texture* wallTop;
	SDL_Texture* wallBott;

	// renderer
	SDL_Renderer* renderer;

	// test map roughly conforms to screen bounds
	int map[18][31];

public:

	// constructor/destructor
	Map(SDL_Renderer* _renderer);
	~Map();

	// methods
	void LoadMap(int arr[18][31]);
	void DrawMap();
};