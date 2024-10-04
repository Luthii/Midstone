#include "Character.h"

// The constructor thingy
Character::Character(
    const std::string& name_, const std::string& occupation_,
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_, float radius_, float orientation_,
    float rotation_, float angular_) : Body{ pos_, vel_, accel_, mass_, radius_, orientation_, rotation_, angular_ }, name{ name_ }, occupation{ occupation_ } {}

// Destructor
Character::~Character() {}
