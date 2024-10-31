#pragma once

#include <string>
#include <vector>

#include "Entity.h"

#define FRAMES_PER_SECONDS 24
#define DELTA_FRAME 0.1f

struct AnimationInfo {
	std::string name;
	TILE beginTile;
	unsigned int numberSprites;
};

class Animation : public Entity
{
public:
	//initiates with the animation of the charlie walk sprite sheet
	std::vector<AnimationInfo> walkAnimation = {
		AnimationInfo{"walk_up", TILE{0,0}, 6},
		AnimationInfo{"walk_down", TILE{0,16}, 6},
		AnimationInfo{"walk_left", TILE{0,32}, 6},
		AnimationInfo{"walk_right", TILE{0,48}, 6}
	};
	AnimationInfo currentAnimation = walkAnimation[0];
	int currentFrame = 0;
	float elapsedTime = 0.0f;

	Animation(SDL_Renderer* sceneRenderer_, Vec3 pos_) : Entity(pos_, "textures/charlie_walk.png", sceneRenderer_) {
		std::cout << "DELTA FRAME: " << DELTA_FRAME << "\n";
	}

	virtual void HandleEvents() {}
	virtual void Update(float deltaTime) {
		elapsedTime += deltaTime;

		if (elapsedTime >= DELTA_FRAME) {
			//we are changing the current frame
			currentFrame++;

			//if we hit the end of the sprite animation, reset to the first one
			if (currentFrame >= currentAnimation.numberSprites)
				currentFrame = 0;

			//reset elapsed time
			elapsedTime = 0.0f;
		}

		
	}

	virtual void Render(SDL_Renderer* sceneRenderer) {
		SDL_Rect tileTexClip;
		SDL_Rect tileRectScreen;

		//tile on the screen
		tileRectScreen.x = static_cast<int> (position.x - Camera::cameraX);
		tileRectScreen.y = static_cast<int> (position.y - Camera::cameraY);
		tileRectScreen.w = TILE_RENDER_SIZE;
		tileRectScreen.h = TILE_RENDER_SIZE;

		//clips the tile map texture. It defines the tile to be rendered.
		tileTexClip.x = currentAnimation.beginTile.x + (currentFrame * TILE_SIZE);
		tileTexClip.y = currentAnimation.beginTile.y * TILE_SIZE;
		tileTexClip.w = TILE_SIZE;
		tileTexClip.h = TILE_SIZE;

		SDL_RenderCopyEx(sceneRenderer, texture, &tileTexClip, &tileRectScreen, 0.0, nullptr, SDL_FLIP_NONE);
	}
};

