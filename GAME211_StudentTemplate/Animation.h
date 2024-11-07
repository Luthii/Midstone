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
	unsigned int numberSprites;
};

class Animation
{
private:
	SDL_Rect currentFrameSprite;
	std::vector<AnimationInfo> walkAnimation = {
	AnimationInfo{"walk_up", TILE{0,0}, 6},
	AnimationInfo{"walk_down", TILE{0,16}, 6},
	AnimationInfo{"walk_left", TILE{0,32}, 6},
	AnimationInfo{"walk_right", TILE{0,48}, 6}
	};

	std::vector<AnimationInfo> animation;
	AnimationInfo currentAnimation = walkAnimation[0];
	int currentFrame = 0;
	float elapsedTime = 0.0f;
	//initiates with the animation of the charlie walk sprite sheet


public:
	Animation(std::string fileName);

	void Update(float deltaTime);
	SDL_Rect getCurrentFrameSprite() { return currentFrameSprite; }
};
