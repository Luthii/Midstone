#include "Object.h"

Object::Object(std::string filePath_, SDL_Renderer* sceneRenderer_)
{
    filePath = filePath_;
    sceneRenderer = sceneRenderer_;

    TEX_object = nullptr;
    SPR_object = nullptr;
}

Object::~Object()
{
    SDL_DestroyTexture(TEX_object);
    TEX_object = nullptr;

    SDL_FreeSurface(SPR_object);
    SPR_object = nullptr;
}

bool Object::OnCreate()
{
    SDL_Surface* SPR_object;
    SPR_object = IMG_Load(filePath.c_str());

    if (SPR_object == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }

    TEX_object = SDL_CreateTextureFromSurface(sceneRenderer, SPR_object);
    if (TEX_object == nullptr) {
        std::cerr << "Erro creating texture from: " << filePath << std::endl;
        return false;
    }

    return true;
}

bool Object::OnDestroy()
{
    SDL_DestroyTexture(TEX_object);
    TEX_object = nullptr;

    return true;
}

void Object::HandleEvents()
{
    //key Down event -> movent character and play walking animation
    if (InputManager::getInstance()->IsKeyDown(SDLK_w))
        velocity.y = -1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_s))
        velocity.y = 1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_a))
        velocity.x = -1.0f;

    if (InputManager::getInstance()->IsKeyDown(SDLK_d))
        velocity.x = 1.0f;
    

    //key UP event -> set animation to stoped at direction
    if (InputManager::getInstance()->IsKeyUp(SDLK_w))
        velocity.y = 0.0f;

    if (InputManager::getInstance()->IsKeyUp(SDLK_s))
       velocity.y = 0.0f;

    if (InputManager::getInstance()->IsKeyUp(SDLK_a))
        velocity.x = 0.0f;

    if (InputManager::getInstance()->IsKeyUp(SDLK_d))
        velocity.x = 0.0f;
}

void Object::Update(float deltaTime)
{
    position += velocity * speed;
}

void Object::Render(SDL_Renderer* sceneRenderer)
{
    SDL_Rect rect;
 
    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    MATH::Vec3 screenCoordinates = Camera::ToScreenCoordinates(position);
   
    rect.x = static_cast<int>(screenCoordinates.x);
    rect.y = static_cast<int>(screenCoordinates.y);
    rect.w = TILE_RENDER_SIZE;
    rect.h = TILE_RENDER_SIZE;

    SDL_RenderCopyEx(sceneRenderer, TEX_object, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);
}
