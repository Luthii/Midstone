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

void Object::Update(float deltaTime)
{
}

void Object::Render(SDL_Renderer* sceneRenderer)
{
    SDL_Rect rect;
    Matrix4 projectionMatrix = Matrix4();//game->getProjectionMatrix();

    Vec3 screenCoords = projectionMatrix * position;

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    rect.x = static_cast<int>(screenCoords.x - (0.5f * SPR_object->w));
    rect.y = static_cast<int>(screenCoords.y - (0.5f * SPR_object->h));
    rect.w = static_cast<int>(SPR_object->w);
    rect.h = static_cast<int>(SPR_object->h);

    SDL_RenderCopyEx(sceneRenderer, TEX_object, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);
}
