#include "Entity.h"

Entity::Entity(){
    pos = Vec3(0, 0, 0);
    vel = Vec3(0, 0, 0);
    accel = Vec3(0, 0, 0);
    mass = 1.0f;
    radius = 1.0f;
    orientation = 0.0f;
    rotation = 0.0f;
    angular = 0.0f;
}

Entity::Entity(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, float radius_, float orientation_, float rotation_, float angular_){
    pos = pos_;
    vel = vel_;
    accel = accel_;
    mass = mass_;
    radius = radius_;
    orientation = orientation_;
    rotation = rotation_;
    angular = angular_;
}

Entity::~Entity(){
}

void Entity::Update(float deltaTime)
{
}

bool Entity::onCreate()
{
    return false;
}

bool Entity::onDestroy()
{
    return false;
}

void Entity::ApplyForce(Vec3 force_)
{
}

void Entity::HandleEvents(const SDL_Event& event)
{
}
