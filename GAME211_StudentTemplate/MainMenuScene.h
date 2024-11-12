#pragma once
#include "Scene.h"
#include "Button.h"

class MainMenuScene : public Scene {
private:
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;
	Player* player;

	Button* btPlay;
	Button* btQuit;

public:
	MainMenuScene(SDL_Window* sdl_Window);
	~MainMenuScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents();
	SDL_Window* getWindow() { return window; }
	SDL_Renderer* getRenderer() { return renderer; }
	virtual void setPlayer(Player* player_) { player = player_; }
	void ResetScene() {}

};

