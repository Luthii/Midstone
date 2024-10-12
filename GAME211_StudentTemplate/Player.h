#pragma once
#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include "Character.h"
// will include object h right??

class Player : public Character{
private :
	int money = 0;
	// add something for inventory

public:
	Player();
	~Player();
	

	void handleInput(SDL_Event& event);
	
	void collectItem();
};

#endif PLAYER_H