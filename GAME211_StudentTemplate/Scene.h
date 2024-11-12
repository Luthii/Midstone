#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>

//project includes
#include "Player.h"
#include "Camera.h"
//#include "GameManager.h"

using namespace MATH;

class Scene {
public:
    //class GameManager* game = NULL;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
    virtual void HandleEvents() = 0;
    virtual ~Scene(){};
	virtual SDL_Window* getWindow() = 0;
	virtual SDL_Renderer* getRenderer() = 0;
	virtual void setPlayer(Player* player_) = 0;
	virtual void ResetScene() = 0;
};

#endif
