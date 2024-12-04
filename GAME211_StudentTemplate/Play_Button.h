#pragma once
#include "Button.h"
#include "Event.h"
#include "EventHandler.h"

class Play_Button : public Button {
public:
	Play_Button(Vec3 position_, std::string name_, SDL_Renderer* sceneRenderer_) : Button(position_, name_, sceneRenderer_) {}
	virtual ~Play_Button() {}

	virtual void OnButtonPressed() {
		EventHandler::GetInstance()->Broadcast(ChangeSceneEvent(SCENES::SHOP_SCENE));

	}
};
