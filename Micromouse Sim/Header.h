#pragma once

#include<raylib.h>
#include<raymath.h>
#include<vector>

using namespace std;

class Cam {
public:
	Camera3D myCam;
	float R;
	const float R_MIN = 100.0f;
	const float R_MAX = 200.0f;
	float pitch;
	float yaw;
	const float PITCH_LIMIT_MAX = PI/2 - 0.01f;
	const float PITCH_LIMIT_MIN = 0.5;

	Cam();

	void update();

};


class Labyrinth {
public:
	vector<bool> myLabyrinth;

	Labyrinth(int size);

	int numberOfFieldsSQR;
	int sizeGameField;
	int sizeQuadrant;

	void draw();

};