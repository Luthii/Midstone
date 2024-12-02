#include "Character.h"

void Character::Update(float deltaTime)
{
	position += velocity * speed;
}

void Character::TakeDamage(float dmg) {
	velocity = Vec3(0.0f, 0.0f, 0.0f);
	setHealth(health - dmg);

	if (health > 0) {
		std::string animationName;

		animationName = "hurt_";
		if (orientation.x > 0) {//player is going right - priorize side movement
			animationName += "right";
		}
		else if (orientation.x < 0) {
			animationName += "left";
		}
		else if (orientation.y > 0) {
			animationName += "down";
		}
		else if (orientation.y < 0) {
			animationName += "up";
		}
		characterAnimation->ChangeAnimation(animationName);
	}
	if (health < 0)
		health = 0;
	if (health == 0)
		Die();
}

void Character::Die() {
	velocity = Vec3(0.0f, 0.0f, 0.0f);
	characterAnimation->ChangeAnimation("die");
	
	
	if (tag == "Player")
	{
		tag = "dead";
	}

	if (tag == "Enemy")
	{
		tag = "dead";
	}
}