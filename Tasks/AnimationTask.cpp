/*
	-------------------- ANIMATION TASK --------------------------------

	Sprite Sheet and XML
- Take a look at the character sprite sheet and decide on the structure of the XML that will describe the sprite sheet of the animation
- On Animation.h there is a struct, AnimationInfro, with some important starting infomations:
	* TILE, wich is a struct of two unsigned ints
	* the numberof sprites in the animation
	* the name of the animation
		+ for this one, you have to think how to properly use it. When we press the "d" key, we want out character to move to the right, 
			so we will call on the animation "move_right" for example. We can do that in many ways:
				1. chech the string for words move and righ.
				2. create const variables with the name of all the animations, and then check them agains the name of the animation on the list
					of animation. In this case, should we use a map?
				3. Create an enum with the name of animation and when reading from the xml compare and associte the enum type.
				...
- You will also have to design how do you want to incorporate the animation information to the Classes that we already created. Right now
	our entity and sub classes only have a texture that will use as a fixed object. This texture will be holding the whole sprite sheet for the
	character/player/object. Do you want the Entity class to have the animation component? OF do you want to specialize it and differentiate
	into to animated Entity and Non-animated entity? Weight the pros and cons and come up with a decision.

*/