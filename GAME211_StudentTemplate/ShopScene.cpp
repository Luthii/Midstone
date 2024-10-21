#include "ShopScene.h"

#include <VMath.h>

// See notes about this constructor in Scene1.h.
ShopScene::ShopScene(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

ShopScene::~ShopScene() {
}

bool ShopScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//we can move the camera translatin the ortho matrix
	/*ortho *= MMath::translate(5.0f, 0.0f, 0.0f);*/
	//----------------------------------------------


	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	//map = new Map(renderer);

	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	//map = new Map(renderer);

	//map = new Map("xml/shopTileMap_.xml", "textures/SuperTileSet.png", renderer);
	//map->onCreate();

	testObj = new Object("textures/duck.png", renderer);
	testObj->OnCreate();
	testObj->setPosition(Vec3(500.0f, 300.0f, 0.0f));
	testObj2 = new Object("textures/cactus.png", renderer);
	testObj2->OnCreate();

	//testObj->getPosition().print();
	//viewMatrix.print();

	return true;
}

void ShopScene::OnDestroy() {
	testObj->OnDestroy();
	delete testObj;
}

void ShopScene::Update(const float deltaTime) {

	// Update player
	//game->getPlayer()->Update(deltaTime);
	testObj->Update(deltaTime);
	testObj2->Update(deltaTime);
	Camera::cameraX = (testObj->getPosition().x + 8) - 1000 / 2;
	Camera::cameraY = (testObj->getPosition().y + 8) - 600 / 2;
}

void ShopScene::Render() {
	//clear window with the bracl color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//clear render
	SDL_RenderClear(renderer);

	// render the duck
	testObj->Render(renderer);
	testObj2->Render(renderer);

	//game->RenderPlayer(0.1f);

	SDL_RenderPresent(renderer);
}

void ShopScene::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	//game->getPlayer()->setPos(game->getPlayer()->getPos() + Vec3(1.0f, 0.0f, 0.0f));
	testObj->HandleEvents(event);
	//camera.x = (testObj->getPosition().x + 8) - 1000 / 2;
	//camera.y = (testObj->getPosition().y + 8) - 600 / 2;
}

