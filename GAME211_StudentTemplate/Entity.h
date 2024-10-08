#pragma once
#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>

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
};

