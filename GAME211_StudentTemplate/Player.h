#pragma once

#include "Object.h"
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

	void TestCollision();
	bool Interact();
	void CheckObjectInteractionList(TILE key, unsigned int objectID);
	void AddItemBag(OBJECT_TYPE objType, unsigned int quantity);

protected:

public:
	Player(Vec3 position_, Vec3 velocity_, float speed_, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		Character(position_, velocity_, speed_, texFilePath_, sceneRenderer_) 
	{
		playerAnimation = new Animation("xml/player_animation.xml");
		//Test for event
		//EventHandler::GetInstance()->Subscribe(ScreamEvent::eventType, std::bind(&Player::tempFunction, this, std::placeholders::_1), "Player5");
	}

	~Player();

	void Update(float deltaTime);
	void Render(SDL_Renderer* sceneRender);
	void HandleEvents() override;
	void setCollisionLayer(MapLayer* collisionLayer_) { collisionLayer = collisionLayer_; }

	//test for event
	//void tempFunction(const Event& event) { std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!!!!!\n"; }

};

