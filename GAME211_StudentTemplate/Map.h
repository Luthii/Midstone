#pragma once

//C++ includes
#include <vector>
#include <string>
#include <iostream>

//third party includes
#include "tinyxml2.h"
using namespace tinyxml2;

//project includes
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
	SDL_Renderer* sceneRender;

	// test map roughly conforms to screen bounds
	int map[18][31];

//CAROL's addition
	std::string tileMapTexturePath;
	std::string tileMapXmlPath;
	SDL_Texture* TXT_TileMap;
	// this is a matrix to hold the tile map information.
	//[x][y][layer]
	std::vector<std::vector<std::vector<int>>> tileMap;

	bool ReadXMLTileMap();

public:

	// constructor/destructor
	Map(SDL_Renderer* _renderer);
	Map(std::string tileMapXmlPath_, std::string tileMapTexturePath_, SDL_Renderer* sceneRender_) : tileMapXmlPath{ tileMapXmlPath_ }, tileMapTexturePath{ tileMapTexturePath_ }, sceneRender{ sceneRender_ } {}
	~Map();

	// methods
	bool onCreate();
	void LoadMap(int arr[18][31]);
	void DrawMap();
};