#pragma once

//C++ includes

//project includes
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Animation.h"
#include "Button.h"

class MinesScene1 : public Scene {
private:
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window

	Map* minesMap;
	Player* player;
	//Animation* testAnimation;

public:
	MinesScene1(SDL_Window* sdlWindow);
	~MinesScene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents();
	void setPlayer(Player* player_);
	SDL_Window* getWindow() { return window; }
	SDL_Renderer* getRenderer() { return renderer; }
	void ResetScene();
};
