#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Entity.h" // to be replaced with entity

class Character :public Entity {
protected:
	std::string name; //
	std::string type; // Can be occupation like smith, cook, etc., alternatively monster type 
    int health; // 100
    int speed; // movement speed

public:
    // Constructors
	Character() : Entity{}, name{ "" }, type{ "" } {}
    Character(
        const std::string& name_, 
        const std::string& type_,
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_, float radius_, float orientation_,
        float rotation_, float angular_) : Entity{ pos_, vel_, accel_, mass_, radius_, orientation_, rotation_, angular_ },name{ name_ }, type{ type_ } {}

    ~Character();

    // Getters
    std::string getName() const { return name; }

    // Setters
    void setName(const std::string& name_) { name = name_; }
    void setOccupation(const std::string& type_) { type = type_;}
    void characterMove(int dx, int dy){
        pos.x += dx * speed;
        pos.y += dy * speed;
    }

    void healthCheck();
    virtual void interact() {}

};

#endif CHARACTER_H