#include "MinesScene2.h"
#include <VMath.h>

//Constructor
MinesScene2::MinesScene2(SDL_Window* window_) {
	window = window_;
	renderer = SDL_GetRenderer(window);
	minesMap = nullptr;
	player = nullptr;
}

//Deconstructor
MinesScene2::~MinesScene2() {
}

bool MinesScene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	IMG_Init(IMG_INIT_PNG);

	minesMap = new Map("xml/TM_MinesLevel2.xml", "textures/minesSpriteSheet.png", renderer);
	minesMap->onCreate();

	return 1;
}

void MinesScene2::OnDestroy() {
	minesMap->onDestroy();
	//delete testAnimation;
	delete minesMap;
}

void MinesScene2::Update(const float deltaTime) {
	// run the update function in player
	player->Update(deltaTime);
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

void MinesScene2::Render() {
	// match the bg colour to the scene
	SDL_SetRenderDrawColor(renderer, 46, 34, 47, 0);

	// clear renderer
	SDL_RenderClear(renderer);

	// render scene map
	minesMap->Render(renderer);
	// render player
	player->Render(renderer);

	SDL_RenderPresent(renderer);
}

void MinesScene2::HandleEvents() {
	player->HandleEvents();
}

void MinesScene2::setPlayer(Player* player_) {
	player = player_;
}

void MinesScene2::ResetScene() {
	// set the map collision
	player->setCollisionLayer(minesMap->getCollisionLayer());

	// set the player to the spawn point
	player->setPosition(minesMap->getSpawnPosition());

	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}