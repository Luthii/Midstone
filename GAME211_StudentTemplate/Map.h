#pragma once

//C++ includes
#include <vector>
#include <string>
#include <iostream>

//third party includes
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "tinyxml2.h"
using namespace tinyxml2;

//project includes
#include "DataCollection.h"
#include "Camera.h"

typedef std::vector<std::vector<int>> MapLayer;

class Map {
private:
// renderer
	SDL_Renderer* sceneRender;

	MATH::Vec3 spawnPosition;
	int mapWidth = 0;
	int mapHeight = 0;
	int mapLayers = 0;
	int tileSetWidth = 0;
	int tileSetHeight = 0;
	int collisionLayer = 0;
	std::string tileMapTexturePath;
	std::string tileMapXmlPath;
	SDL_Texture* TEX_TileMap = nullptr;;
	// this is a matrix to hold the tile map information.
	//[layer] [y][x]
	std::vector<MapLayer*> tileMap;

	bool ReadXMLTileMap();
	MapLayer* SliceStr(std::string str, int width, int height, int layer);
	int CountLayer(XMLElement* mapNode);

public:

	// constructor/destructor
	Map(std::string tileMapXmlPath_, std::string tileMapTexturePath_, SDL_Renderer* sceneRender_) : tileMapXmlPath{ tileMapXmlPath_ }, tileMapTexturePath{ tileMapTexturePath_ }, sceneRender{ sceneRender_ } {
	
	}
	~Map();

	// methods
	bool onCreate();
	void onDestroy();
	void Render(SDL_Renderer* renderer);
	MATH::Vec3 getSpawnPosition() { return spawnPosition; };
	//int collisionAt(MATH::Vec3 position);
	MapLayer* getCollisionLayer() { return tileMap.at(collisionLayer); }
};