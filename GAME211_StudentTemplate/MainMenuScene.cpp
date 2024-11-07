#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(SDL_Window* sdl_Window) {
	window = sdl_Window;
	renderer = SDL_GetRenderer(window);

	btPlay = nullptr;
	btQuit = nullptr;

}

MainMenuScene::~MainMenuScene() {
	

}

bool MainMenuScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	btPlay = new Button(Vec3(100, 100, 0), "textures/bt_Play.png", renderer);
	btPlay->onCreate();

	btQuit = new Button(Vec3(500, 100, 0), "textures/bt_Quit.png", renderer);
	btQuit->onCreate();

	std::cout << "Finished creating the shop scene!\n";
	return true;
}

void MainMenuScene::OnDestroy() {
	

}

void MainMenuScene::Update(const float time) {
	

}

void MainMenuScene::Render() {

	//clear window with the bracl color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//clear render
	SDL_RenderClear(renderer);

	btPlay->Render(renderer);
	btQuit->Render(renderer);

	SDL_RenderPresent(renderer);

}


void MainMenuScene::HandleEvents() {
	btQuit->HandleEvents();
}
