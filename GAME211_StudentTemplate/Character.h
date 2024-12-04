#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

/*  ----------------- ABSTRACT CLASS --------------------------

    The character class will define the common attributes of the following classes:
    - Player: the one that the user can control
    - NPC: non-playable characters, but they will move around and the player can interact with them
    - Enemy: non-playable character that can attack the player and be attacked by the player
*/


//C++ includes
#include <string>

//project includes
#include "Entity.h"
#include "Animation.h"

class Character : public Entity {
protected:
    Vec3 velocity = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 orientation = Vec3(0.0f, 1.0f, 0.0f); // character will star looking to the top of the screen
    float speed = 3.0f; // movement speed
    float health = 10.0f;
    const float maxHealth = 100.0f;
    std::string tag;
    Animation* characterAnimation;

public:
    // Constructors
    Character(Vec3 position_, std::string texFilePath_, SDL_Renderer* sceneRenderer_) : 
        Entity(position_, texFilePath_, sceneRenderer_) {}

    Character(std::string tag_, Vec3 position_, Vec3 velocity_, float speed_ ,std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
        Entity(position_, texFilePath_, sceneRenderer_) {
        tag = tag_; velocity = velocity_; speed = speed_;
    }

    virtual ~Character() { std::cerr << "Calling Character destructor..." << std::endl; }

 //HandleEvents will not be implemented in this Class. This class should remain abstract
    //virtual void HandleEvents() = 0;
    virtual void Update(float deltaTime);

//setters and getters
    void setVelocity(Vec3 newVelocity) { velocity = newVelocity; }
    Vec3 getVelocity() { return velocity; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    float getSpeed() { return speed; }
    void setHealth(float newHealth) { health = newHealth; }
    float getHealth() { return health; }

    void TakeDamage(float damage);
    void Die();
};

#endif CHARACTER_H