#include "Character.h"

// The constructor
Character::Character(
    const std::string& name_, const std::string& type_,
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_, float radius_, float orientation_,
    float rotation_, float angular_) : Entity { pos_, vel_, accel_, mass_, radius_, orientation_, rotation_, angular_ }, name{ name_ }, type{ type_ } {}

// Destructor
Character::~Character() {}

void Character::healthCheck() {
    if (health > 0) {
        int i = 0;
        // placeholder for death checks. might migrate this
    }
}
