#include "ShopScene.h"

//third party includes
#include <VMath.h>

void ShopScene::testCollision()
{
	//test collision before moving character
	/*/steps:
		- Get player velocity to find out the direction of the player movement
		- Get player position and transform to tile to find out the players next tile movements
		- Calculate the tiles to be tested
		- Query the map for the tiles
			- Test each tile, and if colision, set the velocity on that direction to zero
				(player->SetVelocity(player->getVelocity() - Vec3(0.0f, -1.0f, 0.0f)); for example.
				this line sets the velocity to the Y vector to be zero in case the player is trying to move UP
				but there is an obstacle
	*/

	//if the object is moving, its velocity is different from 0, so it's velocity vector magnitude is differentfrom zero
	//in this case, test for colision
	if (MATH::VMath::mag(testObj->getVelocity()) != 0) {
		MATH::Vec3 vecAuxAdjancent; //test side
		MATH::Vec3 vecAuxDiagonal; //test bottom or up
		int tileValueAdjacent = -1;
		int tileValueDiagonal = -1;

		//object going righ -> +x
		if (testObj->getVelocity().x > 0.0f)
		{
															//we have to use the speed because the object will move speed pixels
			vecAuxAdjancent = testObj->getPosition() + Vec3(TILE_RENDER_SIZE + testObj->getSpeed(), 0.0f, 0.0f);
			vecAuxDiagonal = testObj->getPosition() + Vec3(TILE_RENDER_SIZE + testObj->getSpeed(), (TILE_RENDER_SIZE - 1), 0.0f);
		}
		//object going left -> -x
		else if (testObj->getVelocity().x < 0.0f)
		{
			vecAuxAdjancent = testObj->getPosition() + Vec3(-testObj->getSpeed(), 0.0f, 0.0f);
			vecAuxDiagonal = testObj->getPosition() + Vec3(-testObj->getSpeed(), (TILE_RENDER_SIZE - 1), 0.0f);
		}

		tileValueAdjacent = shopMap->collisionAt(vecAuxAdjancent);
		tileValueDiagonal = shopMap->collisionAt(vecAuxDiagonal);

		//if tile is bigger than 0, it means there is a object in the map and we should stop our player
		//so set the velocity to zero.
		if (tileValueAdjacent > 0 || tileValueDiagonal > 0) {
			testObj->setVelocity(testObj->getVelocity() + Vec3(-testObj->getVelocity().x, 0.0f, 0.0f));
		}

		//now for the Y axis
		tileValueAdjacent = -1;
		tileValueDiagonal = -1;
		//object going righ -> +y (down the screen)
		if (testObj->getVelocity().y > 0.0f)
		{
			vecAuxAdjancent = testObj->getPosition() + Vec3(0.0f, TILE_RENDER_SIZE + testObj->getSpeed(), 0.0f);
			vecAuxDiagonal = testObj->getPosition() + Vec3((TILE_RENDER_SIZE - 1), TILE_RENDER_SIZE + testObj->getSpeed(), 0.0f);
		}
		//object going left -> -y (up on the screen)
		else if (testObj->getVelocity().y < 0.0f)
		{
			vecAuxAdjancent = testObj->getPosition() + Vec3(0.0f, -testObj->getSpeed(), 0.0f);
			vecAuxDiagonal = testObj->getPosition() + Vec3((TILE_RENDER_SIZE - 1), -testObj->getSpeed(), 0.0f);
		}

		tileValueAdjacent = shopMap->collisionAt(vecAuxAdjancent);
		tileValueDiagonal = shopMap->collisionAt(vecAuxDiagonal);

		//if tile is bigger than 0, it means there is a object in the map and we should stop our player
		//so set the velocity to zero.
		if (tileValueAdjacent > 0 || tileValueDiagonal > 0) {
			testObj->setVelocity(testObj->getVelocity() + Vec3(0.0f, -testObj->getVelocity().y, 0.0f));
		}
	}
}

// See notes about this constructor in Scene1.h.
ShopScene::ShopScene(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
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

	shopMap = new Map("xml/TM_Shop_Collision.xml", "textures/SuperTileSetShop.png", renderer);
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

	testCollision();
	testObj->Update(deltaTime);
	testObj2->Update(deltaTime);
	//update the camera to follow the duck obj
	Camera::UpdateCenterCoordinates(testObj->getPosition().x, testObj->getPosition().y);
}

void ShopScene::Render() {
	//clear window with the bracl color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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

void ShopScene::HandleEvents()
{
	//player moved
	testObj->HandleEvents();
	//test colission
	Vec3 playerDirection = testObj->getVelocity();

}

