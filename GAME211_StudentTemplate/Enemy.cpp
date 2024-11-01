#include "Enemy.h"

Enemy::~Enemy() { 
	std::cout << "Calling Enemy Deconstructor" << std::endl; 
}


void Enemy::HandleEvents() {
	std::cout << "hello !";
}