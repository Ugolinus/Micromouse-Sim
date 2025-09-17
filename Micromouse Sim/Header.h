#pragma once

#include<raylib.h>
#include<raymath.h>
#include<vector>
#include<iostream>
#include <string>

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
	float sizeQuadrant;

	void draw();

};

class Mouse {
public:
	vector<bool> myLabyrinth;
	Color col;
	int pos;
	Vector3 posOnScreen;
	Vector3 posVec;
	Vector3 nowPos;
	Mouse(Color col, int numberOfFieldsSQR, int sizeGameField,float sizeQuadrant, vector<bool> myLabyrinth);

	int mouseBrain();

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;
	vector<int> getSensorData();
	bool makeMove(int direction);

	void draw();
};