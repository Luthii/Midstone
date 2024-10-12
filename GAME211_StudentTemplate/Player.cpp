#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::handleInput(SDL_Event& event){
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            //function here(0, -1);
            break;
        case SDLK_DOWN:
            //function here(0, -1);
            break;
        case SDLK_LEFT:
            //function here(0, -1);
            break;
        case SDLK_RIGHT:
            //function here(0, -1);
            break;
        }
    }
}
