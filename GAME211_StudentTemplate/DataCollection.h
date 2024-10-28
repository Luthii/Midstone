#pragma once
#include "ObjectMap.h"

const int TILE_SIZE = 16;
const int TILE_SCALE = 2;
const int TILE_RENDER_SIZE = TILE_SIZE * TILE_SCALE;

// Use 1000x600 for less than full screen
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 600;

enum SCENES {
	MAIN_MENU,
	SHOP_SCENE
};


