#pragma once
#include "Entity.h"
#include <iostream>


class Button {
protected:
	Vec3 position;
	SDL_Texture* texBTNotPressed;
	SDL_Texture* texBTPressed;
	SDL_Texture* currentTexture;
	std::string name;
	SDL_Renderer* sceneRenderer;

	SDL_Texture* LoadTexture(std::string filePath);

public:
	//ALL entities must have a texture(needs a render to be created) and a position on the scene,
	//	so there is no default constructor with no paramenters
	Button(Vec3 position_, std::string name_, SDL_Renderer* sceneRenderer_) :
		position{ position_ }, name{ name_ }, sceneRenderer{ sceneRenderer_ } {}
	virtual ~Button();

	virtual bool onCreate();

	//to be called in order in the game loop
	/*virtual void HandleEvents() = 0;
	virtual void Update(float deltaTime) = 0;*/
	virtual void Render(SDL_Renderer* sceneRenderer);

	//proteced members setters and getters
	//virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }
	//virtual SDL_Texture* getTexture() { return texture; }
	virtual void setPosition(Vec3 newPosition) { position = newPosition; }
	virtual Vec3 getPosition() { return position; }

	

//public:
//	Button(Vec3 position_, std::string textFilePath_, SDL_Renderer* sceneRender_) :
//		Entity( position_, textFilePath_, sceneRender_ ){}
//
//	~Button(){}
//
	void HandleEvents();
//	void Update(float deltaTime);
//	void Render(SDL_Renderer* sceneRenderer);
//
//
};
//
