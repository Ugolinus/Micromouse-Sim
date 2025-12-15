#pragma once
#include"Header.h"


class Run {

private:
	
	
	
	int id;

	//Interface
	Vector2 pos;
	float height;
	float width;
	Color col;
	Rectangle box;
	Font* p_arial;
	


public:
	int stepsAllowed;
	int stepsLeft;
	bool running;
	bool activated;

	void draw();

	Run(int id, float posX, float posY, float height, float width, int steps, Font* p_arial);

	void isClicked();

	void update();

	void drawStepsCounter();

	void drawTextExCenteredInBox(const std::string& text, float fontSize, float spacing, Color col);
	

};