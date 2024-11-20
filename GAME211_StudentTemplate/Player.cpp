#include "VMath.h"
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

//if the object is moving, its velocity is different from 0, so it's velocity vector magnitude is different from zero
//in this case, test for colision
void Player::TestCollision()
{
	//Vec3 collisionBoxPosition = Vec3(position.x + collisionBox.topLeftCorner.x, )

	if (VMath::mag(velocity) != 0) {
		MATH::Vec3 vecAuxAdjancent; //test side
		MATH::Vec3 vecAuxDiagonal; //test bottom or up
		int tileValueAdjacent = -1;
		int tileValueDiagonal = -1;

		//object going righ -> +x
		if (velocity.x > 0.0f)
		{
			//we have to use the speed because the object will move speed pixels
			vecAuxAdjancent = position + Vec3(collisionBox.bottomRightCorner.x + speed, collisionBox.topLeftCorner.y, 0.0f);
			vecAuxDiagonal = position + Vec3(collisionBox.bottomRightCorner.x + speed, collisionBox.bottomRightCorner.y, 0.0f);
			//vecAuxAdjancent = position + Vec3(TILE_RENDER_SIZE + speed, 0.0f, 0.0f);
			//vecAuxDiagonal = position + Vec3(TILE_RENDER_SIZE + speed, (TILE_RENDER_SIZE - 1), 0.0f);
		}
		//object going left -> -x
		else if (velocity.x < 0.0f)
		{
			vecAuxAdjancent = position + Vec3(collisionBox.topLeftCorner.x - speed, collisionBox.topLeftCorner.y, 0.0f);
			vecAuxDiagonal = position + Vec3(collisionBox.topLeftCorner.x - speed, collisionBox.bottomRightCorner.y, 0.0f);
			//vecAuxAdjancent = position + Vec3(-speed, 0.0f, 0.0f);
			//vecAuxDiagonal = position + Vec3(-speed, (TILE_RENDER_SIZE - 1), 0.0f);
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
			vecAuxAdjancent = position + Vec3(collisionBox.topLeftCorner.x, collisionBox.bottomRightCorner.y + speed, 0.0f);
			vecAuxDiagonal = position + Vec3(collisionBox.bottomRightCorner.x, collisionBox.bottomRightCorner.y + speed, 0.0f);
			//vecAuxAdjancent = position + Vec3(0.0f, TILE_RENDER_SIZE + speed, 0.0f);
			//vecAuxDiagonal = position + Vec3((TILE_RENDER_SIZE - 1), TILE_RENDER_SIZE + speed, 0.0f);
		}
		//object going left -> -y (up on the screen)
		else if (velocity.y < 0.0f)
		{
			vecAuxAdjancent = position + Vec3(collisionBox.topLeftCorner.x, collisionBox.topLeftCorner.y -speed, 0.0f);
			vecAuxDiagonal = position + Vec3(collisionBox.bottomRightCorner.x, collisionBox.topLeftCorner.y - speed, 0.0f);
			//vecAuxAdjancent = position + Vec3(0.0f, -speed, 0.0f);
			//vecAuxDiagonal = position + Vec3((TILE_RENDER_SIZE - 1), -speed, 0.0f);
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

bool Player::Interact()
{
	//std::cout << "Player orientation: ";
	//orientation.print();
	std::cout << "OBJECT_MAP size: " << OBJECT_MAP.size() << std::endl;

	if (VMath::mag(orientation) == 0)
		return false;


	//std::cout << "Test interaction!\n";
	TILE playerTile;
	playerTile.x = position.y / TILE_RENDER_SIZE;
	playerTile.y = position.x / TILE_RENDER_SIZE;
	//std::cout << "Player tile coordinates: " << playerTile.x << "," << playerTile.y << "\n";
	MATH::Vec3 vecAuxAdjancent; //test side
	MATH::Vec3 vecAuxDiagonal; //test bottom or up
	int tileValueAdjacent = -1;
	int tileValueDiagonal = -1;
	TILE tileCoords;
	unsigned int tileID;
	//player is facing left or right
	if (orientation.x != 0) {
		//std::cout << "Interaction on X axis\n";
		//object going righ -> +x
		if (orientation.x > 0.0f)
		{
			//std::cout << "Interaction on +X\n";
			//we have to use the speed because the object will move speed pixels
			vecAuxAdjancent = position + Vec3(TILE_RENDER_SIZE + speed, 0.0f, 0.0f);
			vecAuxDiagonal = position + Vec3(TILE_RENDER_SIZE + speed, (TILE_RENDER_SIZE - 1), 0.0f);
		}
		//object going left -> -x
		else if (orientation.x < 0.0f)
		{
			//std::cout << "Interaction on -X\n";
			vecAuxAdjancent = position + Vec3(-speed, 0.0f, 0.0f);
			vecAuxDiagonal = position + Vec3(-speed, (TILE_RENDER_SIZE - 1), 0.0f);
		}

		tileCoords.x = vecAuxAdjancent.y / TILE_RENDER_SIZE;
		tileCoords.y = vecAuxAdjancent.x / TILE_RENDER_SIZE;
		tileID = unsigned(collisionLayer->at(tileCoords.x).at(tileCoords.y));
		std::cout << "Tile ID: " << tileID << std::endl;
		//priority to the top collision - if no object in the top corner, test the one below it
		if (OBJECT_MAP.find(tileID) == OBJECT_MAP.end() || tileID == 0) {
			tileCoords.x = vecAuxDiagonal.y / TILE_RENDER_SIZE;
			tileCoords.y = vecAuxDiagonal.x / TILE_RENDER_SIZE;
			tileID = unsigned(collisionLayer->at(tileCoords.x).at(tileCoords.y));
			std::cout << "Tile ID: " << tileID << std::endl;

			//no objects on the MAP or in the collision layer
			if (OBJECT_MAP.find(tileID) == OBJECT_MAP.end() || tileID == 0)
				return false;
		}
	}
	//player if facing up or down
	else {
		//std::cout << "Player facing up or down\n";
		//object going righ -> +x
		if (orientation.y > 0.0f)
		{
			//std::cout << "Interaction on +Y\n";
			//we have to use the speed because the object will move speed pixels
			vecAuxAdjancent = position + Vec3(0.0f, TILE_RENDER_SIZE + speed, 0.0f);
			vecAuxDiagonal = position + Vec3((TILE_RENDER_SIZE - 1), TILE_RENDER_SIZE + speed, 0.0f);
		}
		//object going left -> -x
		else if (orientation.y < 0.0f)
		{
			//std::cout << "Interaction on -Y\n";
			vecAuxAdjancent = position + Vec3(0.0f, -speed, 0.0f);
			vecAuxDiagonal = position + Vec3((TILE_RENDER_SIZE - 1), -speed, 0.0f);
		}

		tileCoords.x = vecAuxAdjancent.y / TILE_RENDER_SIZE;
		tileCoords.y = vecAuxAdjancent.x / TILE_RENDER_SIZE;
		tileID = unsigned(collisionLayer->at(tileCoords.x).at(tileCoords.y));
		std::cout << "Tile ID: " << tileID << std::endl;
		//priority to the top collision - if no object in the top corner, test the one below it
		if (OBJECT_MAP.find(tileID) == OBJECT_MAP.end() || tileID == 0) {
			tileCoords.x = static_cast<int>(vecAuxDiagonal.y / TILE_RENDER_SIZE);
			tileCoords.y = static_cast<int>(vecAuxDiagonal.x / TILE_RENDER_SIZE);
			tileID = unsigned(collisionLayer->at(tileCoords.x).at(tileCoords.y));
			std::cout << "Tile ID: " << tileID << std::endl;

			//no objects on the MAP or in the collision layer
			if (OBJECT_MAP.find(tileID) == OBJECT_MAP.end() || tileID == 0)
				return false;
		}
	}

	//std::cout << "Tile coordinates: " << tileCoords.x << "," << tileCoords.y << "\n";
	CheckObjectInteractionList(tileCoords, tileID);

	return true;
}

void Player::CheckObjectInteractionList(TILE key, unsigned int objectID)
{
	std::string animationName;
	//if the code reached here, it means that there is a collidiable object and this object exist in the OBJECT MAP
	//1. lets test if this object is an object that should give an interaction, for example, the anvil should open a craft window
	switch (OBJECT_MAP.at(objectID).type) {
	case OBJECT_TYPE::ANVIL:
		std::cout << "You interacted with the anvil!! In the future you will be able to craft objectes in the future! :)\n";
			break;
	default:
		animationName = "pickaxe_";
		if (orientation.x > 0) {//player is going right - priorize side movement
			animationName += "right";
		}
		else if (orientation.x < 0) {
			animationName += "left";
		}
		else if (orientation.y > 0) {
			animationName += "down";
		}
		else if (orientation.y < 0) {
			animationName += "up";
		}
		playerAnimation->ChangeAnimation(animationName);
		//interacting = true;
		//interactedObjects.find(key);
		if (interactedObjects.find(key) != interactedObjects.end()) {
			//the object was found
			interactedObjects.at(key)->numberInteractions++;
			//std::cout << "Object interacted with already on the list! ID: " << interactedObjects.at(key)->objNumber << std::endl;
		}
		else {
			//first interaction. Creates a new object on the map
			ObjectScene* newObj = new ObjectScene{ 1, objectID };
			interactedObjects.insert(std::pair<TILE, ObjectScene*>(key, newObj));
			//std::cout << "Object interacted with NEW! ID: " << interactedObjects.at(key)->objNumber << std::endl;
		}

		//if the object being interacted with reached the number of interactions necessary to be deleted, remove from map
		if (interactedObjects.at(key)->numberInteractions >= OBJECT_MAP.at(objectID).interactionNumber)
		{
			(*collisionLayer)[key.x][key.y] = 0;
			AddItemBag(OBJECT_MAP.at(objectID).loot, OBJECT_MAP.at(objectID).lootQuantity);
			interactedObjects.erase(key);
		}

		break;
	}

}

void Player::AddItemBag(OBJECT_TYPE objType, unsigned int quantity) {

	//player already has type of item in the bag
	if (playerBag.find(objType) != playerBag.end()) {
		playerBag.at(objType)->quatity += quantity;
	}
	//player has none of the item in the bag
	else {
		ObjectLoot* newObj = new ObjectLoot{ quantity };
		playerBag.insert(std::pair<OBJECT_TYPE, ObjectLoot*>(objType, newObj));
	}
}

void Player::Update(float deltaTime) {
	position += velocity * speed;

	//set animation
	std::string animationName;
	if (VMath::mag(velocity) == 0) {//player is not moving - select idle animation
		animationName = "idle_";
	}
	else { //player is moving - select walk animation
		animationName = "walk_";
	}

	if (orientation.x > 0) {//player is going right - priorize side movement
		animationName += "right";
	}
	else if (orientation.x < 0) {
		animationName += "left";
	}
	else if (orientation.y > 0) {
		animationName += "down";
	}
	else if (orientation.y < 0) {
		animationName += "up";
	}

	//if(!interacting)
		playerAnimation->ChangeAnimation(animationName);
	playerAnimation->Update(deltaTime);
}

void Player::Render(SDL_Renderer* sceneRender) {
	SDL_Rect rect;
	SDL_Rect clip = playerAnimation->getCurrentFrameSprite();
	MATH::Vec3 screenCoordinates = Camera::ToScreenCoordinates(position);

	rect.x = static_cast<int>(screenCoordinates.x + (playerAnimation->getCurrentAnimationInfo().anchor_x * TILE_SCALE));
	rect.y = static_cast<int>(screenCoordinates.y + (playerAnimation->getCurrentAnimationInfo().anchor_y * TILE_SCALE));
	rect.w = clip.w * TILE_SCALE;
	rect.h = clip.h * TILE_SCALE;

	SDL_RenderCopyEx(sceneRenderer, texture, &clip, &rect, 0.0, nullptr, SDL_FLIP_NONE);
}

void Player::HandleEvents()
{
	if (playerAnimation->getLockState())
		return;

    //key Down event -> movent character and play walking animation
    if (InputManager::getInstance()->IsKeyDown(SDLK_w))
        velocity.y = -1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_s))
        velocity.y = 1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_a))
        velocity.x = -1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_d))
        velocity.x = 1.0f;

	if(VMath::mag(velocity) != 0)
		orientation = velocity; //saves the orientation of the character

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

	// changed from ->IsKeyDown to ->IsKeyUp
	if (InputManager::getInstance()->IsKeyUp(SDLK_SPACE)) {
		//std::cout << "\n-------------------------------------------------------\n";
		//std::cout << "Space bar pressed\n";
		Interact();
		//std::cout << "\n-------------------------------------------------------\n";
	}


	//Test for event
	//if (InputManager::getInstance()->IsKeyUp(SDLK_l))
	//	EventHandler::GetInstance()->Unsubscribe(ScreamEvent::eventType, "Player5");


}
