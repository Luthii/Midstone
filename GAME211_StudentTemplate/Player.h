#pragma once

#include "ObjectMap.h"
#include "Map.h"
#include "Character.h"
#include "EventHandler.h"

class GameManager;

extern std::map<unsigned int, Object> OBJECT_MAP;

class Player : public Character
{
private:
	MapLayer* collisionLayer;
	std::map<TILE, ObjectScene*, TILE_Comparator> interactedObjects;
	std::map<OBJECT_TYPE, ObjectLoot*> playerBag;
	COLLISION_BOX collisionBox;
	bool interacting = false;
	int mineLevel;
	float buffer;

	void TestCollision();
	bool Interact();
	void Attack();
	void CheckObjectInteractionList(TILE key, unsigned int objectID);
	void AddItemBag(OBJECT_TYPE objType, unsigned int quantity);

protected:

public:
	Player(std::string tag_, Vec3 position_, Vec3 velocity_, float speed_, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		Character(tag_, position_, velocity_, speed_, texFilePath_, sceneRenderer_) 
	{
		collisionBox.topLeftCorner.x = 2;
		collisionBox.topLeftCorner.y = 6;
		collisionBox.bottomRightCorner.x = 14 * TILE_SCALE;
		collisionBox.bottomRightCorner.y = 16 * TILE_SCALE;
		characterAnimation = new Animation("xml/player_animation.xml");
		std::cout << "Player created!\n";
	}

	~Player();

	void Update(float deltaTime);
	void Render(SDL_Renderer* sceneRender);
	void HandleEvents() override;
	void setCollisionLayer(MapLayer* collisionLayer_) { collisionLayer = collisionLayer_; }

};

