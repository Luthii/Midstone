#include "ShopScene.h"

//third party includes
#include <VMath.h>

// See notes about this constructor in Scene1.h.
ShopScene::ShopScene(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_GetRenderer(window);
	shopMap = nullptr;
	player = nullptr;
	//testAnimation = nullptr;
	btPlay = nullptr;
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

	btPlay = new Button(Vec3(100, 100, 0), "textures/bt_Play.png", renderer);
	btPlay->onCreate();

	std::cout << "Finished creating the shop scene!\n";
	return true;
}

void ShopScene::OnDestroy() {
	shopMap->onDestroy();
	//delete testAnimation;
	delete shopMap;
}

void ShopScene::Update(const float deltaTime) {

	player->Update(deltaTime);
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);
	//testAnimation->Update(deltaTime);
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
	//testAnimation->Render(renderer);

	btPlay->Render(renderer);

	SDL_RenderPresent(renderer);
}

void ShopScene::HandleEvents()
{
	player->HandleEvents();
	btPlay->HandleEvents();
	//Test for event
	//if (InputManager::getInstance()->IsKeyUp(SDLK_p))
	//	EventHandler::GetInstance()->Broadcast(ScreamEvent());
}

void ShopScene::setPlayer(Player* player_)
{
	player = player_;
	player->setCollisionLayer(shopMap->getCollisionLayer());
	player->setPosition(shopMap->getSpawnPosition());
	Camera::UpdateCenterCoordinates(player->getPosition().x, player->getPosition().y);

	//testAnimation = new Animation(renderer, player->getPosition());
	//testAnimation->onCreate();
}

