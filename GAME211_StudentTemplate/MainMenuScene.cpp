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

	btPlay = new Play_Button(Vec3(100, 100, 0), "Play", renderer);
	btPlay->onCreate();

	

	btQuit = new Quit_Button(Vec3(500, 100, 0), "Quit", renderer);
	btQuit->onCreate();

	btPlay->SetNext(btQuit);
	btQuit->SetPrev(btPlay);

	selectedButton = btPlay;
	selectedButton->SelectButton();

	std::cout << "Finished creating the main menu scene!\n";
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
	btPlay->HandleEvents();

	if (InputManager::getInstance()->IsKeyDown(SDLK_a)) {
		if (!(selectedButton->GetPrev() == nullptr)) {
			selectedButton->UnSelectedButton();
			selectedButton = selectedButton->GetPrev();
			selectedButton->SelectButton();
		}
	}

	if (InputManager::getInstance()->IsKeyDown(SDLK_d)) {
		if (!(selectedButton->GetNext() == nullptr)) {
			selectedButton->UnSelectedButton();
			selectedButton = selectedButton->GetNext();
			selectedButton->SelectButton();
		}
	}

	if (InputManager::getInstance()->IsKeyDown(SDLK_SPACE)) {
		selectedButton->OnButtonPressed();

		/*if (!(selectedButton->OnButtonPress() == nullptr)) {
			selectedButton->UnSelectedButton();
			selectedButton = selectedButton->GetNext();
			selectedButton->SelectButton();
		}*/
	}

}
