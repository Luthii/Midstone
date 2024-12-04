#pragma once
#include "Button.h"
#include "Event.h"
#include "EventHandler.h"

class Quit_Button : public Button {
public:
	Quit_Button(Vec3 position_, std::string name_, SDL_Renderer* sceneRenderer_) : Button(position_, name_, sceneRenderer_) {}
	virtual ~Quit_Button() {}

	virtual void OnButtonPressed() {
		EventHandler::GetInstance()->Broadcast(QuitEvent());

	}
};

