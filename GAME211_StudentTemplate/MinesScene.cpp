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
		
	std::cout << key << "\n";

	switch (key)
	{
		// When the player chooses to enter the mines, they are placed in one of our three mine floors
	case (0):
		minesMap = new Map("xml/TM_MinesLevel1.xml", "textures/minesSpriteSheet.png", renderer);
		minesMap->onCreate();
		return 1;
	case (1):
		minesMap = new Map("xml/TM_MinesLevel2.xml", "textures/minesSpriteSheet.png", renderer);
		minesMap->onCreate();
		return 1;
	case(2):
		minesMap = new Map("xml/TM_MinesLevel3.xml", "textures/minesSpriteSheet.png", renderer);
		minesMap->onCreate();
		return 1;
	}
	return 0;
}

void MinesScene::OnDestroy() {
	minesMap->onDestroy();
	//delete testAnimation;
	delete minesMap;
}

void MinesScene::Update(const float deltaTime) {
	// run the update function in player
	player->Update(deltaTime);
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

void MinesScene::Render() {
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

void MinesScene::HandleEvents() {
	player->HandleEvents();
}

void MinesScene::setPlayer(Player* player_) {
	player = player_;
}

void MinesScene::ResetScene() {
	// set the map collision
	player->setCollisionLayer(minesMap->getCollisionLayer());

	// set the player to the spawn point
	player->setPosition(minesMap->getSpawnPosition());
	
	// center the camera on the player
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}