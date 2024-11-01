#pragma once

#include "Object.h"
#include "Map.h"
#include "Character.h"

class Player : public Character
{
private:
	MapLayer* collisionLayer;
	std::map<TILE, ObjectScene*, TILE_Comparator> interactedObjects;
	std::map<OBJECT_TYPE, ObjectLoot*> playerBag;
	void TestCollision();
	bool Interact();
	void CheckObjectInteractionList(TILE key, unsigned int objectID);
	void AddItemBag(OBJECT_TYPE objType, unsigned int quantity);

protected:

public:
	Player(Vec3 position_, Vec3 velocity_, float speed_, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		Character(position_, velocity_, speed_, texFilePath_, sceneRenderer_) {}

	~Player();

	void HandleEvents() override;
	void setCollisionLayer(MapLayer* collisionLayer_) { collisionLayer = collisionLayer_; }

};

