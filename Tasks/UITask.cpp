/*
	-------------------- UI TASK --------------------------------

	Create the Button class
- It should inherit from the enity class
- It should have two variables to hold the widht and height of the button texture. Once you create the texture, assign the value of its height and width to the variables.
	Remember that the Entity class has a OnCreate event that should be called after the object is created.
- Implement the two virtual functions handle events and update. They can be empty for now.
- Override the render function to use the width and height of the button texture instead of the width height of the TILE_RENDER_SIZE.


	Create MainMenuScene

- It should inherit from Scene.h
- It should include the Button.h file
- It must have two buttons objects, one "Start" and the Other "Quit" (to make it easier, I separated them into two textures: bt_Play.png and bt_Quit.png)
- Set their positions on the scene, any one, as long as they dont overlap, by setting their position variable (a Vec3).

	Game Manager
- On GameManager.h create a scene object called mainMenuScene
- On GameManager.cpp make currentScene = new MainMenuScene(renderer)
- Remove the line: currentScene->setPlayer(player). This should be enough to render the mainMenuScene. If you run into any problem, check if there are no other functions
	calls related to the ShopScene class.

	Go back to the button class
- Now that your buttons are on the scene, implement the handle event.
- When pressing the number 1, make the class print a message to the console saying "you chose to player the game".
- When pressing the number 2, make the class print a message to the console "quitting game!", and call on the QuitGame() method of the InputManager.
	InputManger is a singleton! If you want to call or use it, you must include "InputManger.n" in your file, and to call on the function right InputManger::getIntance().QuitGame();

*/