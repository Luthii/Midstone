#pragma once

#include "ObjectMap.h"
#include "Map.h"
#include "Character.h"
#include "EventHandler.h"
#include "Animation.h"

class Player : public Character
{
private:
	MapLayer* collisionLayer;
	std::map<TILE, ObjectScene*, TILE_Comparator> interactedObjects;
	std::map<OBJECT_TYPE, ObjectLoot*> playerBag;
	Animation* playerAnimation;
	COLLISION_BOX collisionBox;
	bool interacting = false;

	void TestCollision();
	bool Interact();
	void CheckObjectInteractionList(TILE key, unsigned int objectID);
	void AddItemBag(OBJECT_TYPE objType, unsigned int quantity);

protected:

public:
	Player(Vec3 position_, Vec3 velocity_, float speed_, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		Character(position_, velocity_, speed_, texFilePath_, sceneRenderer_) 
	{
		collisionBox.topLeftCorner.x = 2;
		collisionBox.topLeftCorner.y = 6;
		collisionBox.bottomRightCorner.x = 14 * TILE_SCALE;
		collisionBox.bottomRightCorner.y = 16 * TILE_SCALE;
		playerAnimation = new Animation("xml/player_animation.xml");
		std::cout << "Player created!\n";
	}

	~Player();

	void Update(float deltaTime);
	void Render(SDL_Renderer* sceneRender);
	void HandleEvents() override;
	void setCollisionLayer(MapLayer* collisionLayer_) { collisionLayer = collisionLayer_; }

};

