#include "InputManager.h"

void InputManager::cleanKeyBoard()
{
	int i;
	for (i = 0; i < N_KEYS; i++) {
		keyDown[i] = false;
		keyUp[i] = false;
	}
}

void InputManager::Update()
{
    SDL_Event event;
	cleanKeyBoard();
    keyboard = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			keyDown[event.key.keysym.sym] = true;
			keyUp[event.key.keysym.sym] = false;
			break;
		case SDL_KEYUP:
			keyUp[event.key.keysym.sym] = true;
			keyDown[event.key.keysym.sym] = false;
			break;
		case SDL_QUIT:
			quitGame = true;
			break;
		}
	}
}

bool InputManager::IsKeyPressed(const int key) const
{
	if (keyboard[key])
		return true;

	return false;
}
