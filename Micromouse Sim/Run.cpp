#include "Run.h"


Run::Run(int id, float posX,float posY, float height, float width,int steps, Font* p_arial) {
	this->id = id;
	this->pos = {posX,posY};
	this->height = height;
	this->width = width;
	this->col = BLACK;
	this->running=false;
	this->activated=false;
	this->box = {pos.x,pos.y,width,height};
	this->stepsAllowed = steps;
	this->stepsLeft = steps;
	this->p_arial = p_arial;
}

void Run::isClicked()
{
	if (!activated) {
		if (CheckCollisionPointRec(GetMousePosition(),box)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			running = true;
			activated = true;
		}
	}

}

void Run::draw()
{
	if (!running) {
		
		DrawRectangle(box.x, box.y, box.width, box.height, col);
		DrawRectangle(box.x+10, box.y+10, box.width-20, box.height-20, RED);
	} else {

		DrawRectangle(box.x, box.y, box.width, box.height, col);
		DrawRectangle(box.x + 10, box.y + 10, box.width - 20, box.height - 20, GREEN);
	}
	string counterSteps = to_string(stepsLeft);
	string counterStepsAllowed = to_string(stepsAllowed);
	DrawText(counterSteps.c_str(), pos.x + 30, pos.y + 30, 30, BLACK);
	//DrawText(counterStepsAllowed.c_str(), pos.x + 30, pos.y + 30, 30, BLACK);

}

void Run::update()
{
	if (running)
		stepsLeft--;
	if (stepsLeft <= 0)
		running = false;

}
