#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Body.h"

class Character :public Body {
protected:
	std::string name;
	std::string occupation;

public:
    // Constructors
	Character() : Body{}, name{ "" }, occupation{ "" } {}

    Character(
        const std::string& name_, 
        const std::string& occupation_,
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_, float radius_, float orientation_,
        float rotation_, float angular_) : Body{ pos_, vel_, accel_, mass_, radius_, orientation_, rotation_, angular_ },name{ name_ }, occupation{ occupation_ } {}


    // Getters
    std::string getName() const { return name; }

    // Setters
    void setName(const std::string& name_) { name = name_; }
    void setOccupation(const std::string& occupation_) {occupation = occupation_;}
};