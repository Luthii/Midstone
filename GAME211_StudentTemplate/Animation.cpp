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
		animInfo.numberSprites = std::stoi(animData->FirstChildElement("number_of_sprites")->GetText());

		animation.push_back(animInfo);

		animData = animData->NextSiblingElement("Animation");
	}

	//set the current animation to be the first one on the sprite sheet
	currentAnimation = animation[0];

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
