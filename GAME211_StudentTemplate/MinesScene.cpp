#include "MinesScene.h"
#include <VMath.h>

//Constructor
MinesScene::MinesScene(SDL_Window* window_) {
	window = window_;
	renderer = SDL_GetRenderer(window);
	minesMap = nullptr;
	player = nullptr;
}

//Deconstructor
MinesScene::~MinesScene() {
}

bool MinesScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	IMG_Init(IMG_INIT_PNG);

	int key;
	srand(time(0));
	key = rand() % 3;

	switch (key)
	{
		// When the player chooses to enter the mines, they are placed in one of our three mine floors
	case (0):
		minesMap = new Map("xml/TM_MinesLevel1.xml", "textures/SuperTileSetShop.png", renderer);
		minesMap->onCreate();
		break;
	case (1):
		minesMap = new Map("xml/TM_MinesLevel2.xml", "textures/SuperTileSetShop.png", renderer);
		minesMap->onCreate();
		break;
	case(2):
		minesMap = new Map("xml/TM_MinesLevel3.xml", "textures/SuperTileSetShop.png", renderer);
		minesMap->onCreate();
		break;
	}
}

void MinesScene::OnDestroy() {

	delete window;
	
	// destroy renderer and delete var
	SDL_DestroyRenderer(renderer);
	delete renderer;

	// destroy the tile map and delete the var
	minesMap->onDestroy();
	delete minesMap;
	
	// destroy the player and delete the var
	//player->OnDestroy();
	delete player;
}

void MinesScene::Update(const float deltaTime) {
	// run the update function in player
	player->Update(deltaTime);
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

void MinesScene::Render() {
	// set the bg colour to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	// clear renderer
	SDL_RenderClear(renderer);

	// render scene map
	minesMap->Render(renderer);
	// render player
	player->Render(renderer);

	SDL_RenderPresent(renderer);
}

void MinesScene::HandleEvents() {
	player->HandleEvents();
}

void MinesScene::setPlayer(Player* player_) {
	player = player_;
	// set up collisions
	player->setCollisionLayer(minesMap->getCollisionLayer());
	// set the player to the spawn point
	player->setPosition(minesMap->getSpawnPosition());

	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

void MinesScene::ResetScene() {
	// set the player to the spawn point
	player->setPosition(minesMap->getSpawnPosition());
	
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}