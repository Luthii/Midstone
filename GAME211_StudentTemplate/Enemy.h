#pragma once

#include "Character.h"

class Enemy : public Character{
private: 
	int damage;

public: 
	// Constructor / Deconstructor
	Enemy(Vec3 position_, Vec3 velocity_, float speed_, int damage, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		Character(position_, velocity_, speed_, texFilePath_, sceneRenderer_) {}
	~Enemy();

	// Methods
	void HandleEvents() override;
};

