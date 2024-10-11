#include "Map.h"

// This layout represents the map, this will be a xml or txt file later on
int test[18][31] = {
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4 },
	{ 4, 4, 4, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 1, 2, 2, 2, 2, 1, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 2, 0, 0, 0, 0, 2, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 4, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
};


Map::Map(GameManager* game) {
	this->game = game;

	floor = TextureManager::LoadTexture("Art/World/Caves/Backgrounds/tile_mines.png", game->getRenderer());
	wallTop = TextureManager::LoadTexture("Art/World/Caves/Backgrounds/wall_tile_top.png", game->getRenderer());
	wallBott = TextureManager::LoadTexture("Art/World/Caves/Backgrounds/wall_tile_bottom.png", game->getRenderer());

	LoadMap(test);

	source.x = 0;
	source.y = 0;
	dest.x = 0;
	dest.y = 0;

	source.h = 32;
	source.w = 32;
	dest.h = 32;
	dest.w = 32;
}

void Map::LoadMap(int arr[18][31]) {

	for (int row = 0; row < 18; row++) {
		for (int col = 0; col < 31; col++) {
			map[row][col] = arr[row][col];
		}
	}
}

void Map::DrawMap() {

	int tileType = 0;

	for (int row = 0; row < 18; row++) {
		for (int col = 0; col < 31; col++) {
			tileType = map[row][col];

			dest.x = col * 32;
			dest.y = row * 32;

			switch (tileType) {
			case 0:
				TextureManager::Draw(game->getRenderer(), floor, source, dest);
				break;
			case 1:
				TextureManager::Draw(game->getRenderer(), wallTop, source, dest);
				break;
			case 2:
				TextureManager::Draw(game->getRenderer(), wallBott, source, dest);
				break;
			default:
				break;
			}
		}
	}

}