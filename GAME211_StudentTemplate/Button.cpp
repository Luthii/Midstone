#include "Button.h"
#include"InputManager.h"

#include "Entity.h"

SDL_Texture* Button::LoadTexture(std::string filePath)
{
    SDL_Surface* SRF_Entity;
    SDL_Texture* texture;
    SRF_Entity = IMG_Load(filePath.c_str());

    if (SRF_Entity == nullptr) {
        std::cerr << "Can't open the image: " << filePath << std::endl;
        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(sceneRenderer, SRF_Entity);
    if (texture == nullptr) {
        std::cerr << "Erro creating texture from: " << filePath << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(SRF_Entity);

    return texture;
}

Button::~Button()
{
    std::cerr << "Calling Entity destructor..." << std::endl;
    SDL_DestroyTexture(texBTPressed);
    texBTPressed = nullptr;

    SDL_DestroyTexture(texBTNotPressed);
    texBTNotPressed = nullptr;
}

bool Button::onCreate()
{
    std::string filePath = "textures/bt_";
    filePath += name + "_NotPressed.png";
    if ((texBTNotPressed = LoadTexture(filePath)) == nullptr) {
    
        std::cerr << "Erro creating the entity." << std::endl;
        return false;
    }

    filePath = "textures/bt_" + name + "_Pressed.png";
    if ((texBTPressed = LoadTexture(filePath)) == nullptr) {

        std::cerr << "Erro creating the entity." << std::endl;
        return false;
    }

    currentTexture = texBTNotPressed;

    return true;
}

//void Button::Render(SDL_Renderer* sceneRenderer)
//{
//    SDL_Rect rect;
//    MATH::Vec3 screenCoordinates = Camera::ToScreenCoordinates(position);
//
//    rect.x = static_cast<int>(screenCoordinates.x);
//    rect.y = static_cast<int>(screenCoordinates.y);
//    rect.w = TILE_RENDER_SIZE;
//    rect.h = TILE_RENDER_SIZE;
//
//    SDL_RenderCopyEx(sceneRenderer, texBTNotPressed, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);
//}


void Button::HandleEvents() {

	if (InputManager::getInstance()->IsKeyDown(SDLK_7)) {
		std::cout << "button pressed" << std::endl;
        currentTexture = texBTPressed;
	}
	if (InputManager::getInstance()->IsKeyUp(SDLK_7)) {

		std::cout << "button pressed" << std::endl;
        currentTexture = texBTNotPressed;
		//InputManager::getInstance()->QuitGame();
	}



}
//
//void Button::Update(float deltaTime) {
//	
//
//
//}
//
void Button::Render(SDL_Renderer* sceneRenderer) {
	SDL_Rect rect;
	SDL_Point size;
	SDL_QueryTexture(currentTexture, NULL, NULL, &size.x, &size.y);
	MATH::Vec3 screenCoordinates = position;

	rect.x = static_cast<int>(screenCoordinates.x);
	rect.y = static_cast<int>(screenCoordinates.y);
	rect.w = size.x * 1;
	rect.h = size.y * 1;


	SDL_RenderCopyEx(sceneRenderer, currentTexture, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);

}
//
