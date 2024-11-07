#pragma once

//C++ includes

//project includes
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Animation.h"

class ShopScene : public Scene {
private:
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window

	Map* shopMap;
	Player* player;
	//Animation* testAnimation;

public:
	ShopScene(SDL_Window* sdlWindow);
	~ShopScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents();
	void setPlayer(Player* player_);
	SDL_Window* getWindow() { return window; }
	SDL_Renderer* getRenderer() { return renderer; }
};

