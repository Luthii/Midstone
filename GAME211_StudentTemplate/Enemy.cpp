#include "Enemy.h"

Enemy::~Enemy() { 
	std::cout << "Calling Enemy Deconstructor" << std::endl; 
}


void Enemy::HandleEvents() {
	
}

void Enemy::Render(SDL_Renderer* sceneRender) {
	SDL_Rect rect;
	SDL_Rect clip = characterAnimation->getCurrentFrameSprite();
	MATH::Vec3 screenCoordinates = Camera::ToScreenCoordinates(position);

	rect.x = static_cast<int>(screenCoordinates.x + (characterAnimation->getCurrentAnimationInfo().anchor_x * TILE_SCALE));
	rect.y = static_cast<int>(screenCoordinates.y + (characterAnimation->getCurrentAnimationInfo().anchor_y * TILE_SCALE));
	rect.w = clip.w * TILE_SCALE;
	rect.h = clip.h * TILE_SCALE;

	SDL_RenderCopyEx(sceneRenderer, texture, &clip, &rect, 0.0, nullptr, SDL_FLIP_NONE);
}

void Enemy::Update(float deltaTime) {

}