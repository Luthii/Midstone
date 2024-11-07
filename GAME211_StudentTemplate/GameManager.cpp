#include "GameManager.h"
//#include "Scene1.h"


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
    shopScene = nullptr;
    shopScene = nullptr;
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
    shopScene = new ShopScene(windowPtr->GetSDL_Window());
    shopScene->OnCreate();

    mainMenuScene = new MainMenuScene(windowPtr->GetSDL_Window());
    mainMenuScene->OnCreate();

    currentScene = mainMenuScene;
    // need to create Player before validating scene
    if (!ValidateCurrentScene()) {
        std::cerr << "Error creating the default scene." << std::endl;
        OnDestroy();
        return false;
    }
    
    //// create player
    player = new Player(
        Vec3(50.0f, 30.0f, 0.0f),		//position
        Vec3(0.0f, 0.0f, 0.0f),			//velocity
        3.0f,							//speed
        "textures/charlie_walk.png",	//texture file path
        currentScene->getRenderer() 	//scene renderer
    );
    player->onCreate();
    currentScene->setPlayer(player);
      
    //// create an Enemy
    enemy = new Enemy(
        Vec3(50.0f, 30.0f, 0.0f),       //position
        Vec3(0.0f, 0.0f, 0.0f),         //velocity
        1.0f,                           //speed
        20,                             //damage
        "textures/cactus.png",          //texture file path
        currentScene->getRenderer()     //scene renderer
    );
    enemy->onCreate();
    shopScene->setPlayer(player);

	return true;
}


/// Here's the whole game loop
void GameManager::Run() {
    
	timer->Start();
    
	while (!InputManager::getInstance()->IsQuitGame()) {
        
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
    if (currentScene) {
        currentScene->OnDestroy();
        delete currentScene;

    }
    if (player) delete player;
}

SDL_Renderer* GameManager::getRenderer()
{
    // [TODO] might be missing some SDL error checking
    SDL_Window* window = currentScene->getWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    return renderer;
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
