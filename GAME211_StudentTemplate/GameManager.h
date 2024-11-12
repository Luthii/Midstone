#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>

//project includes
#include "DataCollection.h"
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "ShopScene.h"
#include "Player.h"
#include "Enemy.h"
#include "ShopScene.h"
#include "MainMenuScene.h"


class GameManager {
private:
//------------ PRIVATE VARIABLES --------------------
	Window *windowPtr;
	Timer *timer;
	bool isRunning;
	Scene *currentScene;
	Scene* mainMenuScene;
	Scene* shopScene;
	Player* player;
	Enemy* enemy;

//------------ PRIVATE METHODS --------------------
	void handleEvents();
	void LoadScene(int i);
	bool ValidateCurrentScene();

//------------ SINGLETON SETUP --------------------
	//only instance of GameManager
	static GameManager* instance;
	//default constructor is private - Singleton
	GameManager();


public:
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
};
#endif


