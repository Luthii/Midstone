#include "Animation.h"

Animation::Animation(std::string fileName)
{
	//open and xml file and read through it
	std::cout << "Creating animation!\n";
}

void Animation::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= DELTA_FRAME) {
		//we are changing the current frame
		currentFrame++;

		//if we hit the end of the sprite animation, reset to the first one
		if (currentFrame >= currentAnimation.numberSprites)
			currentFrame = 0;

		//clips the tile map texture. It defines the tile to be rendered.
		//updates the date if the frame has changed
		currentFrameSprite.x = currentAnimation.beginTile.x + (currentFrame * TILE_SIZE);
		currentFrameSprite.y = currentAnimation.beginTile.y * TILE_SIZE;
		currentFrameSprite.w = TILE_SIZE;
		currentFrameSprite.h = TILE_SIZE;

		//reset elapsed time
		elapsedTime = 0.0f;
	}
}
