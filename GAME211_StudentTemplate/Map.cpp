#include "Map.h"

// This layout represents the map, this will be a xml or txt file later on
int test[18][31] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

bool Map::ReadXMLTileMap()
{
	XMLDocument tileMapXML;

	if (tileMapXML.LoadFile(tileMapXmlPath.c_str()) != XML_SUCCESS) {
		std::cerr << "Can't open the XML file: " << tileMapXmlPath.c_str() << std::endl;
		return false;
	}

	XMLNode* root = tileMapXML.FirstChild();
	if (root == nullptr) {
		std::cout << "TinyXML2 error: " << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
		return false;
	}

	int mapWidth;
	int mapHeight;
	int mapLayers;

	root->ToElement()->QueryIntAttribute("width", &mapWidth);
	root->ToElement()->QueryIntAttribute("height", &mapHeight);
	root->ToElement()->QueryIntAttribute("nextlayerid", &mapLayers);
	mapLayers--;

	//creates the vector with the size of the tile map to be loaded
	tileMap.assign(mapWidth, std::vector<std::vector<int>>(mapHeight, std::vector<int>(mapLayers, -1)));

	XMLElement* xmlElement;
	std::string str;
	//we are going to loop over the layers of the map and feed our vector
	for (int i = 0; i < mapLayers; i++) {
		xmlElement = root->FirstChildElement("layer")->FirstChildElement("data");
		if (xmlElement == nullptr) {
			std::cout << "TinyXML2 error: " << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
			return false;
		}

		str = xmlElement->GetText();
	}

	return true;
}

// Constructor
Map::Map(SDL_Renderer* _renderer) {
	sceneRender = _renderer;

	floor = TextureManager::LoadTexture("Art/World/Caves/Backgrounds/tile_mines.png", sceneRender);
	wallTop = TextureManager::LoadTexture("Art/World/Caves/Backgrounds/wall_tile_top.png", sceneRender);
	wallBott = TextureManager::LoadTexture("Art/World/Caves/Backgrounds/wall_tile_bottom.png", sceneRender);

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

bool Map::onCreate()
{
	
//load texture of tile map
	SDL_Surface* SPR_tileMap;
	SPR_tileMap = IMG_Load(tileMapTexturePath.c_str());

	if (SPR_tileMap == nullptr) {
		std::cerr << "Can't open the image" << tileMapTexturePath.c_str() << std::endl;
		return false;
	}

	TXT_TileMap = SDL_CreateTextureFromSurface(sceneRender, SPR_tileMap);
	if (TXT_TileMap == nullptr) {
		std::cerr << "Erro creating texture from: " << tileMapTexturePath.c_str() << std::endl;
		return false;
	}

	std::cout << "Tile map: " << tileMapTexturePath.c_str() << " loaded and ready to be used." << std::endl;

//load and read XML of tile map information
	if (ReadXMLTileMap() != true) {
		return false;
	}
}


// Deconstructor
Map::~Map() {

}

// initalize the map array with inputted array
void Map::LoadMap(int arr[18][31]) {

	for (int row = 0; row < 18; row++) {
		for (int col = 0; col < 31; col++) {
			map[row][col] = arr[row][col];
		}
	}
}

// run through the array and render each tile
void Map::DrawMap() {

	// int stores the current value of map[row][col]
	int tileType = 0;

	for (int row = 0; row < 18; row++) {
		for (int col = 0; col < 31; col++) {
			tileType = map[row][col];

			// moves over to the next space
			dest.x = col * 32;
			dest.y = row * 32;

			// earlier tileType int checks which texture to draw
			switch (tileType) {
			case 0:
				TextureManager::Draw(sceneRender, floor, source, dest);
				break;
			case 1:
				TextureManager::Draw(sceneRender, wallTop, source, dest);
				break;
			case 2:
				TextureManager::Draw(sceneRender, wallBott, source, dest);
				break;
			default:
				break;
			}
		}
	}

}