#include "GameManager.h"
#include "MinesScene.h"
//#include "Scene1.h"


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
    shopScene = nullptr;
    shopScene = nullptr;
    minesScene = nullptr;
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

    if (!OBJECT_MAP.OnCreate()) {
        OnDestroy();
        return false;
   }

    // select scene for specific assignment
    shopScene = new ShopScene(windowPtr->GetSDL_Window());
    if (!shopScene->OnCreate()) {
        std::cerr << "Error creating the Shop scene." << std::endl;
        OnDestroy();
        return false;
    }

    mainMenuScene = new MainMenuScene(windowPtr->GetSDL_Window());
    if (!mainMenuScene->OnCreate()) {
        std::cerr << "Error creating the Main Menu scene." << std::endl;
        OnDestroy();
        return false;
    }

    minesScene = new MinesScene(windowPtr->GetSDL_Window());
    if (!minesScene->OnCreate()) {
        std::cerr << "Error creating the Shop scene." << std::endl;
        OnDestroy();
        return false;
    }

    currentScene = minesScene;
    
    //// create player
    player = new Player(
        Vec3(50.0f, 30.0f, 0.0f),		//position
        Vec3(0.0f, 0.0f, 0.0f),			//velocity
        3.0f,							//speed
        "textures/player_spritesheet.png",	//texture file path
        currentScene->getRenderer() 	//scene renderer
    );
    if (!player->onCreate()) {
        std::cerr << "Error creating the player." << std::endl;
        OnDestroy();
        return false;
    }
    currentScene->setPlayer(player);
      
    shopScene->setPlayer(player);

    EventHandler::GetInstance()->Subscribe(QuitEvent::eventType, std::bind(&GameManager::QuitGame, this, std::placeholders::_1), "GameManager");
    EventHandler::GetInstance()->Subscribe(ChangeSceneEvent::eventType, std::bind(&GameManager::ChangeScene, this, std::placeholders::_1), "GameManager");

	return true;
}


/// Here's the whole game loop
void GameManager::Run() {
    
	timer->Start();
    
	while (isRunning) {
        
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

    if (InputManager::getInstance()->IsKeyUp(SDLK_0))
        EventHandler::GetInstance()->Broadcast(QuitEvent());

    if (InputManager::getInstance()->IsKeyUp(SDLK_1))
        EventHandler::GetInstance()->Broadcast(ChangeSceneEvent(SCENES::MAIN_MENU));

    if (InputManager::getInstance()->IsKeyUp(SDLK_2))
        EventHandler::GetInstance()->Broadcast(ChangeSceneEvent(SCENES::SHOP_SCENE));
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

void GameManager::ChangeScene(const Event& event)
{
    const ChangeSceneEvent* changeSceneEvent = dynamic_cast<const ChangeSceneEvent*>(&event);
    switch (changeSceneEvent->sceneChange) {
    case SCENES::MAIN_MENU:
        currentScene = mainMenuScene;
        break;
    case SCENES::SHOP_SCENE:
        currentScene = shopScene;
        break;
    default:
        break;
    }

    currentScene->ResetScene();
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
}
