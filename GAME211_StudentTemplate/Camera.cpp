#include "Camera.h"

float Camera::cameraX = 0.0f;
float Camera::cameraY = 0.0f;
float Camera::cameraCenterX = (SCREEN_WIDTH / 2);
float Camera::cameraCenterY = (SCREEN_HEIGHT / 2);

void Camera::UpdateCenterCoordinates(float x, float y) {
	cameraCenterX = x + PIXEL_SIZE / 2;
	cameraX = cameraCenterX - (SCREEN_WIDTH) / 2;

	cameraCenterY = y + PIXEL_SIZE / 2;
	cameraY = cameraCenterY - (SCREEN_HEIGHT) / 2;

	/*std::cout << "------------------------------------------\n";
	std::cout << "ZOOM CAMERA CENTER: (" << cameraCenterX << "," << cameraCenterY << ")\n";
	std::cout << "CAMERA TOP LEFT CORNER: (" << cameraX << "," << cameraY << ")\n";
	std::cout << "------------------------------------------\n";*/
}

MATH::Vec3 Camera::ToScreenCoordinates(MATH::Vec3 modelCoordinates) {

	float x = modelCoordinates.x - (cameraX);
	float y = modelCoordinates.y - (cameraY);

	return MATH::Vec3(x, y, modelCoordinates.z);
}
