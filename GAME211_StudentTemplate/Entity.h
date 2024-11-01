#pragma once

//third party includes
#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>

//project includes
#include "Camera.h"
#include "InputManager.h"

using namespace MATH;

/*  	----------------- ABSTRACT CLASS --------------------------

	The entity class will define the common attributes of:
	- Character ins the world
	- Objects in the world

*/


class Entity{

//protected because the childs will need access to it
protected:
	Vec3 position;
	SDL_Texture* texture;
	std::string texFilePath;
	SDL_Renderer* sceneRenderer;

	bool LoadTexture();

public: 
//ALL entities must have a texture(needs a render to be created) and a position on the scene,
//	so there is no default constructor with no paramenters
	Entity(Vec3 position_, std::string texFilePath_, SDL_Renderer* sceneRenderer_) :
		position{ position_ }, texFilePath{ texFilePath_ }, sceneRenderer{ sceneRenderer_ } {}
	virtual ~Entity();

	virtual bool onCreate();

//to be called in order in the game loop
	virtual void HandleEvents() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* sceneRenderer);

//proteced members setters and getters
	virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }
	virtual SDL_Texture* getTexture() { return texture; }
	virtual void setPosition(Vec3 newPosition) { position = newPosition; }
	virtual Vec3 getPosition() { return position; }
};