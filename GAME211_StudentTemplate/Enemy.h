#pragma once
#ifndef ENEMY_H
#define ENEMY_H


#include <string>
#include "Character.h"

class Enemy : public Character{
private: 
	int attack = 1;
public: 
	Enemy();
	~Enemy();

	void attackPlayer();
	void deathDrops();
};

#endif ENEMY_H