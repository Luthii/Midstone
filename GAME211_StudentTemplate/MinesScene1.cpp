#include "MinesScene1.h"
#include <VMath.h>

//Constructor
MinesScene1::MinesScene1(SDL_Window* window_) {
	window = window_;
	renderer = SDL_GetRenderer(window);
	minesMap = nullptr;
	player = nullptr;
}

//Deconstructor
MinesScene1::~MinesScene1() {
}

bool MinesScene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	IMG_Init(IMG_INIT_PNG);
		
	minesMap = new Map("xml/TM_MinesLevel1.xml", "textures/minesSpriteSheet.png", renderer);
	minesMap->onCreate();

	return 1;
}

void MinesScene1::OnDestroy() {
	minesMap->onDestroy();
	//delete testAnimation;
	delete minesMap;
}

void MinesScene1::Update(const float deltaTime) {
	// run the update function in player
	player->Update(deltaTime);
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

void MinesScene1::Render() {
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

void MinesScene1::HandleEvents() {
	player->HandleEvents();
}

void MinesScene1::setPlayer(Player* player_) {
	player = player_;
}

void MinesScene1::ResetScene() {
	// set the map collision
	player->setCollisionLayer(minesMap->getCollisionLayer());

	// set the player to the spawn point
	player->setPosition(minesMap->getSpawnPosition());
	
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}