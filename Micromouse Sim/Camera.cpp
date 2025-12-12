#include"Header.h"
#include"Cam.h"

Cam::Cam() {
	this->myCam = {
		//Starpos
		{0,0,0},
		//Goal
		{0,0,0},
		//Up
		{0,1,0},
		//FoV
		25.0f,
		//
		CAMERA_PERSPECTIVE };
	this->R = 100.0f;

	this->pitch = 0.8f, yaw = 0.0f;


}

void Cam::update() {

	if (IsKeyDown(KEY_W)) pitch += 0.005f;
	if (IsKeyDown(KEY_S)) pitch -= 0.005f;
	if (IsKeyDown(KEY_D)) yaw += 0.005f;
	if (IsKeyDown(KEY_A)) yaw -= 0.005f;
	pitch = Clamp(pitch, PITCH_LIMIT_MIN, PITCH_LIMIT_MAX);

	float wheel = GetMouseWheelMove();
	if (wheel != 0.0f) {
		R *= (wheel > 0) ? 0.95f : 1.05f;
		R = Clamp(R, R_MIN, R_MAX);
	}

	this->myCam.position = {
		R * cosf(pitch) * sinf(yaw),
		R * sinf(pitch),
		R * cosf(pitch) * cosf(yaw)
	};

}