#include "Character.h"

void Character::Update(float deltaTime)
{
	position += velocity * speed;
}
