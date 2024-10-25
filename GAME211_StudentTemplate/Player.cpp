#include "Player.h"

Player::~Player() {
	std::cerr << "Calling Player destructor..." << std::endl;
}

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
void Player::TestCollision()
{

	if (MATH::VMath::mag(velocity) != 0) {
		MATH::Vec3 vecAuxAdjancent; //test side
		MATH::Vec3 vecAuxDiagonal; //test bottom or up
		int tileValueAdjacent = -1;
		int tileValueDiagonal = -1;

		//object going righ -> +x
		if (velocity.x > 0.0f)
		{
			//we have to use the speed because the object will move speed pixels
			vecAuxAdjancent = position + Vec3(TILE_RENDER_SIZE + speed, 0.0f, 0.0f);
			vecAuxDiagonal = position + Vec3(TILE_RENDER_SIZE + speed, (TILE_RENDER_SIZE - 1), 0.0f);
		}
		//object going left -> -x
		else if (velocity.x < 0.0f)
		{
			vecAuxAdjancent = position + Vec3(-speed, 0.0f, 0.0f);
			vecAuxDiagonal = position + Vec3(-speed, (TILE_RENDER_SIZE - 1), 0.0f);
		}

		tileValueAdjacent = collisionLayer->at(vecAuxAdjancent.y / TILE_RENDER_SIZE).at(vecAuxAdjancent.x / TILE_RENDER_SIZE);
		tileValueDiagonal = collisionLayer->at(vecAuxDiagonal.y / TILE_RENDER_SIZE).at(vecAuxDiagonal.x / TILE_RENDER_SIZE);

		//if tile is bigger than 0, it means there is a object in the map and we should stop our player
		//so set the velocity to zero.
		if (tileValueAdjacent > 0 || tileValueDiagonal > 0) {
			//testObj->setVelocity(testObj->getVelocity() + Vec3(-testObj->getVelocity().x, 0.0f, 0.0f));
			velocity.x = 0.0f;
		}

		//now for the Y axis
		tileValueAdjacent = -1;
		tileValueDiagonal = -1;
		//object going righ -> +y (down the screen)
		if (velocity.y > 0.0f)
		{
			vecAuxAdjancent = position + Vec3(0.0f, TILE_RENDER_SIZE + speed, 0.0f);
			vecAuxDiagonal = position + Vec3((TILE_RENDER_SIZE - 1), TILE_RENDER_SIZE + speed, 0.0f);
		}
		//object going left -> -y (up on the screen)
		else if (velocity.y < 0.0f)
		{
			vecAuxAdjancent = position + Vec3(0.0f, -speed, 0.0f);
			vecAuxDiagonal = position + Vec3((TILE_RENDER_SIZE - 1), -speed, 0.0f);
		}

		tileValueAdjacent = collisionLayer->at(vecAuxAdjancent.y / TILE_RENDER_SIZE).at(vecAuxAdjancent.x / TILE_RENDER_SIZE);
		tileValueDiagonal = collisionLayer->at(vecAuxDiagonal.y / TILE_RENDER_SIZE).at(vecAuxDiagonal.x / TILE_RENDER_SIZE);

		//if tile is bigger than 0, it means there is a object in the map and we should stop our player
		//so set the velocity to zero.
		if (tileValueAdjacent > 0 || tileValueDiagonal > 0) {
			velocity.y = 0.0f;
		}
	}
}

void Player::HandleEvents()
{
    //key Down event -> movent character and play walking animation
    if (InputManager::getInstance()->IsKeyDown(SDLK_w))
        velocity.y = -1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_s))
        velocity.y = 1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_a))
        velocity.x = -1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_d))
        velocity.x = 1.0f;


    //key UP event -> set animation to stoped at direction
    if (InputManager::getInstance()->IsKeyUp(SDLK_w))
        velocity.y = 0.0f;

    if (InputManager::getInstance()->IsKeyUp(SDLK_s))
        velocity.y = 0.0f;

    if (InputManager::getInstance()->IsKeyUp(SDLK_a))
        velocity.x = 0.0f;

    if (InputManager::getInstance()->IsKeyUp(SDLK_d))
        velocity.x = 0.0f;

	TestCollision();
}
