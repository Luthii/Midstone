#pragma once
#include "Entity.h"
#include <iostream>


class Button : public Entity {
private:
	

public:
	Button(Vec3 position_, std::string textFilePath_, SDL_Renderer* sceneRender_) :
		Entity( position_, textFilePath_, sceneRender_ ){}

	~Button(){}

	void HandleEvents();
	void Update(float deltaTime);
	void Render(SDL_Renderer* sceneRenderer);


};

