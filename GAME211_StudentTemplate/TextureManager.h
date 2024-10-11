#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
	
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect source, SDL_Rect dest);
};