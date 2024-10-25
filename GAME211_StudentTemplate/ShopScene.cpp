#include "ShopScene.h"

//third party includes
#include <VMath.h>

// See notes about this constructor in Scene1.h.
ShopScene::ShopScene(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_GetRenderer(window);
	shopMap = nullptr;
	player = nullptr;
}

ShopScene::~ShopScene() {
}

bool ShopScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
	
	//maybe use this for zoom?
	//SDL_RenderSetLogicalSize(renderer, 640, 400);


	shopMap = new Map("xml/TM_Shop_Collision.xml", "textures/SuperTileSetShop.png", renderer);
	shopMap->onCreate();

	return true;
}

void ShopScene::OnDestroy() {
	shopMap->onDestroy();
	delete shopMap;
}

void ShopScene::Update(const float deltaTime) {

	player->Update(deltaTime);
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

void ShopScene::Render() {
	//clear window with the bracl color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//clear render
	SDL_RenderClear(renderer);

	//render scene map
	shopMap->Render(renderer);

	//render player
	player->Render(renderer);

	SDL_RenderPresent(renderer);
}

void ShopScene::HandleEvents()
{
	player->HandleEvents();
}

void ShopScene::setPlayer(Player* player_)
{
	player = player_;
	player->setCollisionLayer(shopMap->getCollisionLayer());
	player->setPosition(shopMap->getSpawnPosition());
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
}

