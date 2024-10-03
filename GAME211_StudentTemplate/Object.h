#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Object
{
private:
	SDL_Texture* SPR_object; //to start simple, only a single sprite, no animation right now

	//initiate the variables of the sprite to be 16x16 pixels and scale of 1
	int SPR_width = 16;
	int SPR_height = 16;
	int SPR_scale = 1;

	int position[2] = { 0,0 }; //initiate position to (0,0)

public:
	Object(std::string filePath, SDL_Renderer* windowRender);
	~Object();

	void Update(float deltaTime);
	void Render(SDL_Renderer* windowRender);

};

