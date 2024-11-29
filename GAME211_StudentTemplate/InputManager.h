#pragma once

//C++ includes
#include <iostream>

//third party includes
#include <SDL.h>

//project includes
#include "EventHandler.h"

#define N_KEYS 320

class InputManager
{
private:
	const Uint8* keyboard = nullptr;
	bool keyDown[N_KEYS];
	bool keyUp[N_KEYS];
	bool quitGame = false;
	bool lockInput = false;

	static InputManager* instance;
	
	//default constructor
	InputManager() {
		int i;
		for (i = 0; i < N_KEYS; i++) {
			keyDown[i] = false;
			keyUp[i] = false;
		}
	}
	void cleanKeyBoard();

public:
	//"delete" the methods that allow the class to be copied
	InputManager(const InputManager& obj) = delete;
	InputManager& operator=(InputManager const&) = delete;

	static InputManager* getInstance() {
		if (instance == NULL)
			instance = new InputManager();

		return instance;
	}

	void Update();
	bool IsKeyDown(const int key) const { return keyDown[key]; }
	bool IsKeyUp(const int key) const { return keyUp[key]; }
	//bool IsKeyPressed(const int key) const;
	void QuitGame() { quitGame = true; }
	bool IsQuitGame() { return quitGame; }
	void LockInput(/*const Event& event*/) { lockInput = true; cleanKeyBoard(); }
	void UnlockInput(/*const Event& event*/) { lockInput = false; }
	
};

