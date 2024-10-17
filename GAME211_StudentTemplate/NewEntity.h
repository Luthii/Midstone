#pragma once

//C++ includes
#include <iostream>

//third party inclues
#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>

using namespace MATH;

class NewEntity
{
private:
	SDL_Texture* TEX_texture; //to start simple, only a single sprite, no animation right now
	SDL_Surface* SPR_sprite;
	SDL_Renderer* sceneRenderer;

	Vec3 position = Vec3(0.0f, 0.0f, 0.0f);

public:


	Object(std::string filePath_, SDL_Renderer* sceneRenderer_);
	~Object();

	bool OnCreate();
	bool OnDestroy();

	void Update(float deltaTime);
	void Render(SDL_Renderer* windowRender);
};

