#pragma once
#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>

#ifndef ENTITY_H
#define ENTITY_H
using namespace MATH;

class Entity{

protected:
	// Copied from Body.h
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	float orientation;		// facing this direction
	float rotation;			// rotating at this speed
	float angular;          // angular acceleration
	float radius;           // for getting near walls

	Vec3 imageSizeWorldCoords;
	SDL_Surface* image;
	SDL_Texture* texture;
	SDL_Renderer* sceneRenderer;

public: 
	Entity();
	Entity(
		Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_,
		float radius_,
		float orientation_,
		float rotation_,
		float angular_
	);
	~Entity();


	// Graphics and Memory
	virtual void Update(float deltaTime);
	virtual bool onCreate();
	virtual bool onDestroy();
	virtual void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_){imageSizeWorldCoords = imageSizeWorldCoords_;}

	virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }
	virtual SDL_Texture* getTexture() { return texture; }
	virtual void setImage(SDL_Surface* image_) { image = image_; }
	virtual SDL_Surface* getImage() { return image; }


	// Physics
	virtual void ApplyForce(Vec3 force_);
	virtual Vec3 getPos() { return pos; }
	virtual Vec3 getVel() { return vel; }
	virtual Vec3 getAccel() { return accel; }
	virtual float getMass() { return mass; }
	virtual float getOrientation() { return orientation; }
	virtual float getRotation() { return rotation; }
	virtual float getAngular() { return angular; }

	// User Interaction
	virtual void HandleEvents(const SDL_Event& event);
};

#endif ENTITY_H