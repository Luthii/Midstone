#pragma once
#include "Entity.h"
#include <iostream>


class Button {
protected:
	Vec3 position;
	SDL_Texture* texBTNotPressed;
	SDL_Texture* texBTPressed;
	SDL_Texture* currentTexture;
	SDL_Texture* texBTHighlighted;
	std::string name;
	SDL_Renderer* sceneRenderer;

	SDL_Texture* LoadTexture(std::string filePath);

	bool isSelected = false;

	Button* prev = nullptr;
	Button* next = nullptr;

public:
	//ALL entities must have a texture(needs a render to be created) and a position on the scene,
	//	so there is no default constructor with no paramenters
	Button(Vec3 position_, std::string name_, SDL_Renderer* sceneRenderer_) :
		position{ position_ }, name{ name_ }, sceneRenderer{ sceneRenderer_ } {}
	virtual ~Button();

	virtual bool onCreate();

	virtual void Render(SDL_Renderer* sceneRenderer);
	virtual void setPosition(Vec3 newPosition) { position = newPosition; }
	virtual Vec3 getPosition() { return position; }

	void SelectButton() { isSelected = true; currentTexture = texBTHighlighted; }
	void UnSelectedButton() { isSelected = false; currentTexture = texBTNotPressed; }

	void SetNext(Button* _next) { next = _next; }
	void SetPrev(Button* _prev) { prev = _prev; }

	Button* GetNext() { return next; }
	Button* GetPrev() { return prev; }
	
	virtual void OnButtonPressed() = 0;
	
	void HandleEvents();

};
//
