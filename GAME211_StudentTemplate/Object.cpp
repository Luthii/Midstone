#include "Object.h"

Object::Object(std::string filePath_, SDL_Renderer* sceneRenderer_, Vec3* camera_)
{
    filePath = filePath_;
    sceneRenderer = sceneRenderer_;

    TEX_object = nullptr;
    SPR_object = nullptr;
    camera = camera_;

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

void Object::HandleEvents(const SDL_Event& sdlEvent)
{
    //const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    //if (currentKeyStates[SDL_SCANCODE_UP])
    //{
    //    position -= Vec3(0.0f, 1.0f, 0.0f);
    //    if (currentKeyStates[SDL_SCANCODE_LEFT])
    //        position -= Vec3(1.0f, 0.0f, 0.0f);
    //}
    //else if (currentKeyStates[SDL_SCANCODE_DOWN])
    //{
    //    position += Vec3(0.0f, 1.0f, 0.0f);
    //}
    //else if (currentKeyStates[SDL_SCANCODE_LEFT])
    //{
    //    position -= Vec3(1.0f, 0.0f, 0.0f);
    //}
    //else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    //{
    //    position += Vec3(1.0f, 0.0f, 0.0f);
    //}


    if (sdlEvent.type == SDL_KEYDOWN)
    {
        switch (sdlEvent.key.keysym.sym)
        {
        case SDLK_UP:
            velocity = Vec3(0.0f, -1.0f, 0.0f);
            break;

        case SDLK_DOWN:
            velocity = Vec3(0.0f, 1.0f, 0.0f);
            break;

        case SDLK_LEFT:
            velocity = Vec3(-1.0f, 0.0f, 0.0f);
            break;

        case SDLK_RIGHT:
            velocity = Vec3(1.0f, 0.0f, 0.0f);
            break;

        default:
            break;
        }
    }
    
    if (sdlEvent.type == SDL_KEYUP) {
        switch (sdlEvent.key.keysym.sym)
        {
        case SDLK_UP:
            velocity = Vec3(0.0f, 0.0f, 0.0f);
            break;

        case SDLK_DOWN:
            velocity = Vec3(0.0f, 0.0f, 0.0f);
            break;

        case SDLK_LEFT:
            velocity = Vec3(0.0f, 0.0f, 0.0f);
            break;

        case SDLK_RIGHT:
            velocity = Vec3(0.0f, 0.0f, 0.0f);
            break;

        default:
            break;
        }
    }
}

void Object::Update(float deltaTime)
{
    position += velocity * speed;
}

void Object::Render(SDL_Renderer* sceneRenderer, Vec3 camera)
{
    SDL_Rect rect;
    Matrix4 projectionMatrix = Matrix4();//game->getProjectionMatrix();

    Vec3 screenCoords = projectionMatrix * position;

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    rect.x = static_cast<int>(position.x - camera.x);// -(0.5f * 16.0f));
    rect.y = static_cast<int>(position.y - camera.y);// (0.5f * 16.0f));
    rect.w = static_cast<int>(PIXEL_SIZE*2);
    rect.h = static_cast<int>(PIXEL_SIZE*2);

    SDL_RenderCopyEx(sceneRenderer, TEX_object, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);
}
