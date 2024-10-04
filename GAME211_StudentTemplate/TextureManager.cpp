#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* renderer) {

	SDL_Surface* temp = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp);

	SDL_FreeSurface(temp);

	return tex;
}

void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect source, SDL_Rect dest) {
	SDL_RenderCopy(renderer, tex, &source, &dest);
}