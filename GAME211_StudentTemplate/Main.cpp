#include <iostream>

#include "InputManager.h"
#include "EventHandler.h"
#include "GameManager.h"
#include "ObjectMap.h"

//create the InputManager/EventHandler singleton
InputManager* InputManager::instance = nullptr;
EventHandler* EventHandler::instance = nullptr;
GameManager* GameManager::instance = nullptr;
//std::map<unsigned int, Object> OBJECT_MAP;



int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it

	//GameManager::getInstance();
	bool status = GameManager::getInstance()->OnCreate();
	if (status == true) {
		GameManager::getInstance()->Run();
	} else if (status == false) {
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}
	GameManager::getInstance()->OnDestroy();
	return 0;

}
