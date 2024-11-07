#include "Button.h"
#include"InputManager.h"



void Button::HandleEvents() {

	if (InputManager::getInstance()->IsKeyDown(SDLK_1)) {
		std::cout << "button pressed" << std::endl;
	}
	if (InputManager::getInstance()->IsKeyUp(SDLK_1)) {

		std::cout << "button pressed" << std::endl;
		InputManager::getInstance()->QuitGame();
	}



}

void Button::Update(float deltaTime) {
	


}

void Button::Render(SDL_Renderer* sceneRenderer) {
	SDL_Rect rect;
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	MATH::Vec3 screenCoordinates = position;

	rect.x = static_cast<int>(screenCoordinates.x);
	rect.y = static_cast<int>(screenCoordinates.y);
	rect.w = size.x * 0.2;
	rect.h = size.y * 0.2;


	SDL_RenderCopyEx(sceneRenderer, texture, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);

}

