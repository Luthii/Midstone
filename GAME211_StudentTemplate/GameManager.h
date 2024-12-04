#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>

//project includes
//#include "DataCollection.h"
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "ShopScene.h"
//#include "MinesScene.h"
//#include "Player.h"
#include "MainMenuScene.h"
#include "ObjectMap.h"

class Player;

class GameManager {
private:
//------------ PRIVATE VARIABLES --------------------
	Window *windowPtr;
	Timer *timer;
	bool isRunning;
	Scene *currentScene;
	Scene* mainMenuScene;
	Scene* shopScene;
	//Scene* minesScene;
	Player* player;

//------------ PRIVATE METHODS --------------------
	void handleEvents();
	void LoadScene(int i);

//------------ SINGLETON SETUP --------------------
	//only instance of GameManager
	static GameManager* instance;
	//default constructor is private - Singleton
	GameManager();


public:
	// ----------------- VARIABLES --------------
	ObjectMapClass OBJECT_MAP;

	// ----------------- METHODS --------------
	//"delete" the methods that allow the class to be copied
	GameManager(const GameManager& obj) = delete;
	GameManager& operator=(GameManager const&) = delete;

	static GameManager* getInstance() {
		if (instance == NULL)
			instance = new GameManager();

		return instance;
	}


	~GameManager();
	bool OnCreate();
	void OnDestroy();
	void Run();
	SDL_Renderer* getRenderer();
	void QuitGame(const Event& event) { isRunning = false; }
	void ChangeScene(const Event& event);
};
#endif


