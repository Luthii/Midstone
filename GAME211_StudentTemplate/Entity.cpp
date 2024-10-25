#include "Entity.h"

bool Entity::LoadTexture()
{
    SDL_Surface* SRF_Entity;
    SRF_Entity = IMG_Load(texFilePath.c_str());

    if (SRF_Entity == nullptr) {
        std::cerr << "Can't open the image: " << texFilePath << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(sceneRenderer, SRF_Entity);
    if (texture == nullptr) {
        std::cerr << "Erro creating texture from: " << texFilePath << std::endl;
        return false;
    }

    SDL_FreeSurface(SRF_Entity);

    return true;
}

Entity::~Entity()
{
    std::cerr << "Calling Entity destructor..." << std::endl;
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

bool Entity::onCreate()
{
    if (!LoadTexture()) {
        std::cerr << "Erro creating the entity." << std::endl;
        return false;
    }

    return true;
}

void Entity::Render(SDL_Renderer* sceneRenderer)
{
    SDL_Rect rect;
    MATH::Vec3 screenCoordinates = Camera::ToScreenCoordinates(position);

    rect.x = static_cast<int>(screenCoordinates.x);
    rect.y = static_cast<int>(screenCoordinates.y);
    rect.w = TILE_RENDER_SIZE;
    rect.h = TILE_RENDER_SIZE;

    SDL_RenderCopyEx(sceneRenderer, texture, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);
}
