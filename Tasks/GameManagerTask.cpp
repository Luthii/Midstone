/*
	Transform the GameManager class into a singleton
- To make our game have the same structure of a game built in an engine, we should transform our GameManager class into a singleton.
	A singleton is a class that can only have one instance (one object). The InputManager is a singleton. We create them in the main.cpp
	and everyone that includes "InputManage.h" can call on the instance create on the main bu calling InputManage::getInstance().
- Make the proper adjustments to the GameManager class to became a singleton
- Create the GameManager intance on the main.cpp
- Go through the project and see how used the GameManager and adapt the code to the new Singleton logic.

*/