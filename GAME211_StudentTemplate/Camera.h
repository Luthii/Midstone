#pragma once

#include "Vector.h"
#include "DataCollection.h"

class Camera
{
public:
	static float cameraX;
	static float cameraY;
	static float cameraCenterX;
	static float cameraCenterY;

	static void UpdateCenterCoordinates(float x, float y);
	static MATH::Vec3 ToScreenCoordinates(MATH::Vec3 modelCoordinates);
};

