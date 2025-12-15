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
	/*if (!running) {
		
		DrawRectangle(box.x, box.y, box.width, box.height, col);
		DrawRectangle(box.x+10, box.y+10, box.width-20, box.height-20, RED);
	} else {

		DrawRectangle(box.x, box.y, box.width, box.height, col);
		DrawRectangle(box.x + 10, box.y + 10, box.width - 20, box.height - 20, GREEN);
	}*/
	string counterSteps = to_string(stepsLeft);
	string counterStepsAllowed = to_string(stepsAllowed);
	
	//DrawText(counterStepsAllowed.c_str(), pos.x + 30, pos.y + 30, 30, BLACK);


	drawStepsCounter();

}

void Run::update()
{
	if (running)
		stepsLeft--;
	if (stepsLeft <= 0)
		running = false;

}

void Run::drawStepsCounter()
{
	
	float w = box.width / 1.0f;
	float h = box.height / 5.0f;

	
	float x = pos.x + (box.width - w) * 0.5f;
	float y = pos.y + (box.height - h) * 0.5f;

	DrawRectangle((int)x, (int)y, (int)w, (int)h, BLACK);

	float prozent = 0.0f;
	if (stepsAllowed > 0) prozent = (float)stepsLeft / (float)stepsAllowed;
	if (prozent < 0.0f) prozent = 0.0f;
	if (prozent > 1.0f) prozent = 1.0f;

	DrawRectangle((int)(x + 4), (int)(y + 4),
		(int)((w - 8) * prozent), (int)(h - 8), WHITE);

	if (prozent < 0.5)
		col = WHITE;
	else
		col = BLACK;

	if(running)
	drawTextExCenteredInBox(to_string(stepsLeft), h, 1,col);
	else if(activated)
		drawTextExCenteredInBox("Over", h, 1, col);
	else if (!activated)
		drawTextExCenteredInBox("Start Run", h, 1, col);

}

void Run::drawTextExCenteredInBox(const std::string& text, float fontSize, float spacing, Color col)
{
	Vector2 size = MeasureTextEx(*p_arial, text.c_str(), fontSize, spacing);

	Vector2 p;
	p.x = pos.x + (box.width - size.x) * 0.5f;
	p.y = pos.y + (box.height - size.y) * 0.5f;


	DrawTextEx(*p_arial, text.c_str(), p, fontSize, spacing, col);
}




