#include "Map.h"

bool Map::onCreate()
{

	//load texture of tile map
	SDL_Surface* SPR_tileMap;
	SPR_tileMap = IMG_Load(tileMapTexturePath.c_str());

	if (SPR_tileMap == nullptr) {
		std::cerr << "Can't open the image" << tileMapTexturePath.c_str() << std::endl;
		return false;
	}

	TEX_TileMap = SDL_CreateTextureFromSurface(sceneRender, SPR_tileMap);
	if (TEX_TileMap == nullptr) {
		std::cerr << "Erro creating texture from: " << tileMapTexturePath.c_str() << std::endl;
		return false;
	}
	SDL_QueryTexture(TEX_TileMap, NULL, NULL, &tileSetWidth, &tileSetHeight);
	tileSetWidth = tileSetWidth / TILE_SIZE;
	tileSetHeight = tileSetHeight / TILE_SIZE;

	SDL_FreeSurface(SPR_tileMap);
	std::cout << "Tile map: " << tileMapTexturePath.c_str() << " loaded and ready to be used." << std::endl;

	//load and read XML of tile map information
	if (ReadXMLTileMap() != true) {
		return false;
	}

	return true;
}

// Deconstructor
Map::~Map() {

}
void Map::onDestroy()
{
	SDL_DestroyTexture(TEX_TileMap);
	TEX_TileMap = nullptr;
}

bool Map::ReadXMLTileMap()
{
	//open an XML file to be read
	XMLDocument tileMapXML;

	if (tileMapXML.LoadFile(tileMapXmlPath.c_str()) != XML_SUCCESS) {
		std::cerr << "Can't open the XML file: " << tileMapXmlPath.c_str() << std::endl;
		return false;
	}

	//gets the ROOT element of the xml file
	XMLNode* root = tileMapXML.FirstChild();
	if (root == nullptr) {
		std::cout << "TinyXML2 error: " << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
		return false;
	}

	//Gets the first element of the xml file that has the tag "map"
	//retrives the attributes of width and height from the tab
	root = root->NextSiblingElement("map");
	root->ToElement()->QueryIntAttribute("width", &mapWidth);
	root->ToElement()->QueryIntAttribute("height", &mapHeight);

//------------------------------------------------------
// CHANGE THIS TO READ FROM THE FILE
	spawnPosition.x = 9 * TILE_RENDER_SIZE;
	spawnPosition.y = 30 * TILE_RENDER_SIZE;


	//Start to read the nodes with the tag "layer"
	XMLElement* layerNode;
	std::string str;
	layerNode = root->FirstChildElement("layer");
	//count how many layers the map has. Since using tiled we can receive some wrong numbers about the number of layers
	//present in the final version of the map, we chose to create this functions.
	mapLayers = CountLayer(layerNode);

	//creates the vector with the size of the tile map to be loaded
	//3D "matrix", x is the number of collumns, y the number of rows, z the number of layers
	tileMap.assign(mapWidth, std::vector<std::vector<int>>(mapHeight, std::vector<int>(mapLayers, -1)));

	//temp node to hold the information of the node with the tab "data"
	XMLElement* layerData;
	for(int layerNumber = 0; layerNumber < mapLayers; layerNumber++) {
		layerData = layerNode->FirstChildElement("data");
		if (layerData == nullptr) {
			std::cout << "TinyXML2 error: " << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
			std::cout << "Layer has no data node." << std::endl;
			return false;
		}

		str = layerData->GetText();

		SliceStr(str, mapWidth, mapHeight, layerNumber);
		//next node with "layer" tag
		layerNode = layerNode->NextSiblingElement("layer");
	}

	return true;
}


// Method to parse a string element. It will slice the string everytime it finds a comma and the items read until the comma
//will be converted to an integer number.
//Paramenters:
//int widht: number of columns in the map
//int height: number of rows in the map
//int layer: the current layer that is being processed
void Map::SliceStr(std::string str, int width, int height, int layer) {
	//string to hold the elements between two commas on the string
	std::string str2;
	int row = 0;
	int col = -1;
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == '\n') {
			col++;
			row = 0;
			continue;
		}
		if (str[i] == ',') {
			tileMap[row][col][layer] = std::stoi(str2);
			row++;
			//std::cout << str2 << std::endl;
			str2.clear();
			continue;
		}
		str2 += str[i];
	}
}

int Map::CountLayer(XMLElement* layerNode_)
{
	int layers = 0;
	//we are going to loop over the layers of the map and feed our vector
	while (layerNode_ != NULL) {
		layers++;
		layerNode_ = layerNode_->NextSiblingElement("layer");
	}
	return layers;
}

//Renders the tle map
void Map::Render(SDL_Renderer* renderer)
{
	SDL_Rect tileRectScreen;
	SDL_Rect tileTexClip;
	int row;
	int col;
	int tileNumber;
	//three for loops, outer: layer, middle: height, inner: width
	for (int i = 0; i < mapLayers; i++) {
		for (int j = 0; j < mapHeight; j++) {
			for (int k = 0; k < mapWidth; k++) {
				tileNumber = tileMap[k][j][i] - 1;
				row = tileNumber / tileSetWidth; // y
				col = tileNumber % tileSetWidth; // x

				//defines the position and the size of the tile to be rendered in the screen
				tileRectScreen.x = static_cast<int> ((k * TILE_RENDER_SIZE) - Camera::cameraX);
				tileRectScreen.y = static_cast<int> ((j * TILE_RENDER_SIZE) - Camera::cameraY);
				tileRectScreen.w = TILE_RENDER_SIZE;
				tileRectScreen.h = TILE_RENDER_SIZE;

				//clips the tile map texture. It defines the tile to be rendered.
				tileTexClip.x = col * TILE_SIZE;
				tileTexClip.y = row * TILE_SIZE;
				tileTexClip.w = TILE_SIZE;
				tileTexClip.h = TILE_SIZE;

				SDL_RenderCopyEx(renderer, TEX_TileMap, &tileTexClip, &tileRectScreen, 0.0, nullptr, SDL_FLIP_NONE);
			}
		}
	}
}