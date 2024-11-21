#include <sstream>

#include "Animation.h"
using namespace tinyxml2;

Animation::Animation(std::string fileName)
{
	//initializing variables
	currentFrameSprite = { 0,0,TILE_RENDER_SIZE, TILE_RENDER_SIZE };

	//reading the xml file of the animation information
	XMLDocument animXML;
	if (animXML.LoadFile(fileName.c_str()) != XML_SUCCESS) {
		std::cerr << "Can't open the xml file: " << fileName.c_str() << "\n";
		return;
	}

	// gets the root element of the xml file
	XMLNode* root = animXML.FirstChild();

	XMLElement* animData;
	AnimationInfo animInfo;

	animData = root->FirstChildElement("Animation");

	while (animData != nullptr) {
		animInfo.name = animData->FirstChildElement("name")->GetText();
		animInfo.beginTile.x = std::stoi(animData->FirstChildElement("x")->GetText());
		animInfo.beginTile.y = std::stoi(animData->FirstChildElement("y")->GetText());
		animInfo.width = std::stoi(animData->FirstChildElement("w")->GetText());
		animInfo.height = std::stoi(animData->FirstChildElement("h")->GetText());
		animInfo.anchor_x = std::stoi(animData->FirstChildElement("anchor_x")->GetText());
		animInfo.anchor_y = std::stoi(animData->FirstChildElement("anchor_y")->GetText());
		animInfo.loop = std::stoi(animData->FirstChildElement("loop")->GetText());
		animInfo.numberSprites = std::stoi(animData->FirstChildElement("number_of_sprites")->GetText());

		animation.push_back(animInfo);

		animData = animData->NextSiblingElement("Animation");
	}

	//set the current animation to be the first one on the sprite sheet
	currentAnimation = animation.back();
	//currentAnimation = animation[9];

	currentFrameSprite.x = currentAnimation.beginTile.x + (currentFrame * currentAnimation.width);
	currentFrameSprite.y = currentAnimation.beginTile.y * TILE_SIZE;
	currentFrameSprite.w = currentAnimation.width;
	currentFrameSprite.h = currentAnimation.height;

}

void Animation::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= DELTA_FRAME) {
		//we are changing the current frame
		currentFrame++;

		//if we hit the end of the sprite animation, reset to the first one
		if (currentFrame >= currentAnimation.numberSprites) {
			if(!currentAnimation.loop)
			{
				std::string newAnimationName = "idle_" + currentAnimation.name.substr(currentAnimation.name.find("_") + 1);
				//std::cout << newAnimationName << std::endl;
				lockState = false;
				//InputManager::getInstance()->UnlockInput();
				ChangeAnimation(newAnimationName);
				
			}
			currentFrame = 0;
		}
			

		//clips the tile map texture. It defines the tile to be rendered.
		//updates the date if the frame has changed
		currentFrameSprite.x = currentAnimation.beginTile.x + (currentFrame * currentAnimation.width);
		currentFrameSprite.y = currentAnimation.beginTile.y * TILE_SIZE;
		currentFrameSprite.w = currentAnimation.width;
		currentFrameSprite.h = currentAnimation.height;

		//reset elapsed time
		elapsedTime = 0.0f;
	}
}

void Animation::ChangeAnimation(std::string animationName)
{
	if (lockState)
		return;

	if (animationName == currentAnimation.name)
		return;

	for (AnimationInfo animationInfo : animation) {
		if (animationInfo.name == animationName) {
			currentAnimation = animationInfo;
			lockState = !animationInfo.loop;
			if (lockState)
				//InputManager::getInstance()->LockInput();
			currentFrame = 0;
			elapsedTime = 0.0f;
			currentFrameSprite.x = currentAnimation.beginTile.x + (currentFrame * currentAnimation.width);
			currentFrameSprite.y = currentAnimation.beginTile.y * TILE_SIZE;
			currentFrameSprite.w = currentAnimation.width;
			currentFrameSprite.h = currentAnimation.height;
			break;
		}
	}
}
