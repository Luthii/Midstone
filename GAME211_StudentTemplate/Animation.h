#pragma once

//C++ includes
#include <string>
#include <vector>
#include <SDL.h>

//Third party includes
#include "Vector.h"
#include "tinyxml2.h"

//Project includes
#include "DataCollection.h"
#include "Camera.h"

#define FRAMES_PER_SECONDS 24
#define DELTA_FRAME 0.1f

struct AnimationInfo {
	std::string name;
	TILE beginTile;
	int width;
	int height;
	int anchor_x;
	int anchor_y;
	unsigned int numberSprites;
};

class Animation
{
private:
	SDL_Rect currentFrameSprite;
	std::vector<AnimationInfo> animation;
	AnimationInfo currentAnimation;
	int currentFrame = 0;
	float elapsedTime = 0.0f;
	//initiates with the animation of the charlie walk sprite sheet


public:
	Animation(std::string fileName);

	void Update(float deltaTime);
	SDL_Rect getCurrentFrameSprite() const { return currentFrameSprite; }
	AnimationInfo getCurrentAnimationInfo() const { return currentAnimation; }
	void ChangeAnimation(std::string animationName);
};
