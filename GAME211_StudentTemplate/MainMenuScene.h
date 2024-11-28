#pragma once
#include "Scene.h"
#include "Button.h"
#include "Play_Button.h"
#include "Quit_Button.h"

class MainMenuScene : public Scene {
private:
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;
	Player* player;

	Button* btPlay;
	Button* btQuit;
	Button* selectedButton = nullptr;

	SDL_Texture* background;


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

