#include "ShopScene.h"

#include <VMath.h>

// See notes about this constructor in Scene1.h.
ShopScene::ShopScene(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1000.0f;
	yAxis = 600.0f;
	shopMap = nullptr;
	testObj = nullptr;
	testObj2 = nullptr;
}

ShopScene::~ShopScene() {
}

bool ShopScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	Matrix4 ortho2 = MMath::orthographic(-450.0, 550.0f, -250.0f, 350.0f, 0.0f, 1.0f);

	projectionMatrix = ndc * ortho2;


	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
	
	//maybe use this for zoom?
	//SDL_RenderSetLogicalSize(renderer, 640, 400);

	testObj = new Object("textures/duck.png", renderer);
	testObj->OnCreate();
	testObj->setPosition(Vec3(50.0f, 30.0f, 0.0f));
	testObj2 = new Object("textures/cactus.png", renderer);
	testObj2->setPosition(Vec3(0.0f, 0.0f, 0.0f));
	testObj2->OnCreate();
	Camera::UpdateCenterCoordinates(testObj->getPosition().x, testObj->getPosition().y);

	shopMap = new Map("xml/TM_Shop.xml", "textures/SuperTileSetShop.png", renderer);
	shopMap->onCreate();
	testObj->setPosition(shopMap->getSpawnPosition());

	return true;
}

void ShopScene::OnDestroy() {
	testObj->OnDestroy();
	delete testObj;

	testObj2->OnDestroy();
	delete testObj;

	shopMap->onDestroy();
	delete shopMap;
}

void ShopScene::Update(const float deltaTime) {

	testObj->Update(deltaTime);
	testObj2->Update(deltaTime);
	//update the camera to follow the duck obj
	Camera::UpdateCenterCoordinates(testObj->getPosition().x, testObj->getPosition().y);
}

void ShopScene::Render() {
	//clear window with the bracl color
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
	//clear render
	SDL_RenderClear(renderer);

	//render scene map
	shopMap->Render(renderer);

	// render the duck
	testObj->Render(renderer);
	//render cactus
	testObj2->Render(renderer);

	SDL_RenderPresent(renderer);
}

void ShopScene::HandleEvents(const SDL_Event& sdlEvent)
{
	testObj->HandleEvents(sdlEvent);

	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_z:
			break;
		case SDLK_x:
			break;
		default:
			break;
		}
	}
}

