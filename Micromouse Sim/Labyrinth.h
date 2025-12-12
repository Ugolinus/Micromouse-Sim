#pragma once
#include"Header.h"

class Labyrinth {
public:
	vector<bool> myLabyrinth;
	vector<bool>* p_brainLabyrinth;
	Labyrinth(int size, Shader& sh);

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;


	Model model;
	Model ground;
	Model ball;
	Texture2D ball_tex;
	Texture2D tex;
	Texture2D tex_floor;

	void unload();

	void draw(Shader& sh);
};