#include <iostream>

#include "InputManager.h"
#include "EventHandler.h"
#include "GameManager.h"

//create the InputManager/EventHandler singleton
InputManager* InputManager::instance = nullptr;
EventHandler* EventHandler::instance = nullptr;


int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it

	GameManager *ptr = new GameManager();
	bool status  = ptr->OnCreate();
	if (status == true) {
		ptr->Run();
	} else if (status == false) {
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}
	ptr->OnDestroy();
	delete ptr;
	return 0;

}
