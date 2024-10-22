#include "GameManager.h"
//#include "Scene1.h"
#include "ShopScene.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
    //player = nullptr;
}

bool GameManager::OnCreate() {

    windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

    // select scene for specific assignment

    currentScene = new ShopScene(windowPtr->GetSDL_Window());
    
    //// create player
    //float mass = 1.0f;
    //float radius = 0.5f;
    //float orientation = 0.0f;
    //float rotation = 0.0f;
    //float angular = 0.0f;
    ////Vec3 position(0.5f * currentScene->getxAxis(), 0.5f * currentScene->getyAxis(), 0.0f);
    //Vec3 position(0.0f, 0.0f, 0.0f);
    //Vec3 velocity(0.0f, 0.0f, 0.0f);
    //Vec3 acceleration(0.0f, 0.0f, 0.0f);

    //player = new PlayerBody
    //(
    //    position,
    //    velocity,
    //    acceleration,
    //    mass,
    //    radius,
    //    orientation,
    //    rotation,
    //    angular,
    //    this
    //);
    //if ( player->OnCreate() == false ) {
    //    OnDestroy();
    //    return false;
    //}

    // need to create Player before validating scene
    if (!ValidateCurrentScene()) {
        OnDestroy();
        return false;
    }
           
	return true;
}


/// Here's the whole game loop
void GameManager::Run() {
    
	timer->Start();
    
	while (!InputManager::getInstance()->QuitGame()) {
        
        handleEvents();
		timer->UpdateFrameTicks();
        currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

void GameManager::handleEvents() 
{
    InputManager::getInstance()->Update();
    currentScene->HandleEvents();
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}

// This might be unfamiliar
float GameManager::getSceneHeight() { return currentScene->getyAxis(); }

// This might be unfamiliar
float GameManager::getSceneWidth() { return currentScene->getxAxis(); }

// This might be unfamiliar
//Matrix4 GameManager::getProjectionMatrix()
//{ return currentScene->getProjectionMatrix(); }

// This might be unfamiliar
SDL_Renderer* GameManager::getRenderer()
{
    // [TODO] might be missing some SDL error checking
    SDL_Window* window = currentScene->getWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    return renderer;
}

// This might be unfamiliar
void GameManager::RenderPlayer(float scale)
{
    //player->Render(scale);
}

void GameManager::LoadScene( int i )
{
    // cleanup of current scene before loading another one
    currentScene->OnDestroy();
    delete currentScene;

    switch ( i )
    {
        case 1:
            currentScene = new ShopScene( windowPtr->GetSDL_Window());
            break;
        default:
            currentScene = new ShopScene( windowPtr->GetSDL_Window());
            break;
    }

    // using ValidateCurrentScene() to safely run OnCreate
    if (!ValidateCurrentScene())
    {
        isRunning = false;
    }
}

bool GameManager::ValidateCurrentScene()
{
    if (currentScene == nullptr) {
        return false;
    }
    if (currentScene->OnCreate() == false) {
        return false;
    }
    return true;
}
