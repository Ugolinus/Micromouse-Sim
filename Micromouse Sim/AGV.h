#pragma once
#include"Header.h"

class AGV {
public:
	vector<bool> myLabyrinth;
	Color col;
	int pos;

	Direction orientation;

	Vector3 posOnScreen;
	Vector3 posVec;
	Vector3 nowPos;
	AGV(Color col, int numberOfFieldsSQR, int sizeGameField, float sizeQuadrant, vector<bool> myLabyrinth, Shader& sh);

	Direction AGVBrain();

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;
	vector<int> getSensorData();
	bool makeMove(Direction direction);

	Model model;
	Texture2D tex;

	void draw(Shader& sh);

	void unload();
};