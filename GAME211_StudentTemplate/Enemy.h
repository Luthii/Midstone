#pragma once

#include "ObjectMap.h"
#include "Map.h"
#include "Character.h"

class Enemy : public Character{
private: 
	int damage;
	MapLayer* collisionLayer;
	COLLISION_BOX collisionBox;
	
	
	void Attack();

public: 
	// Constructor / Deconstructor
	Enemy(std::string tag_, Vec3 position_, Vec3 velocity_, float speed_, int damage, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		Character(tag_, position_, velocity_, speed_, texFilePath_, sceneRenderer_) {
		collisionBox.topLeftCorner.x = 2;
		collisionBox.topLeftCorner.y = 6;
		collisionBox.bottomRightCorner.x = 14 * TILE_SCALE;
		collisionBox.bottomRightCorner.y = 16 * TILE_SCALE;
		characterAnimation = new Animation("xml/player_animation.xml");
		std::cout << "Player created!\n";
	}

	~Enemy();

	// Methods
	void Update(float deltaTime);
	void Render(SDL_Renderer* sceneRender);
	void HandleEvents() override;
	void setCollisionLayer(MapLayer* collisionLayer_) { collisionLayer = collisionLayer_; }
};

