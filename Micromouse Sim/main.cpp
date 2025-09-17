#include"Header.h"

int main() {

//	Font arial = LoadFontEx("arial.ttf", 40, 0, 0);

	const int HEIGHT = 2000;
	const int WIDTH = 2000;
	const int OFFSET = 150;
	const int FONTSIZE = 50;

	//SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(HEIGHT, WIDTH, "Micromouse Simulator");
	
	Cam myCamera;

	SetTargetFPS(60);


	Labyrinth myLaby(30);
	Mouse myMouse(PINK,myLaby.numberOfFieldsSQR,myLaby.sizeGameField,myLaby.sizeQuadrant,myLaby.myLabyrinth);


	//Zeit controll
	float interval = 0.5f;
	float lastCall = 0.0;

	while (!WindowShouldClose()) {

		//Vollbild umschalten



		//Update
		myCamera.update();
		float t = GetTime();

		if (t - lastCall >= interval) {
			while (!myMouse.makeMove(myMouse.mouseBrain())) {
			};
			lastCall = t;
		}
		



		BeginDrawing();

		BeginMode3D(myCamera.myCam);
		//DrawGrid(4, 10);
	
		ClearBackground(BLACK);

		//Test 

		myLaby.draw();
		myMouse.draw();

		EndMode3D();

		DrawText( "Micro Mouse Simulator",  (WIDTH - MeasureText("Micro Mouse Simulator", FONTSIZE)) / 2.0f, OFFSET , FONTSIZE, LIGHTGRAY);
		DrawLineEx({ 0, HEIGHT - 2*OFFSET }, { WIDTH, HEIGHT - 2 * OFFSET },5, LIGHTGRAY);


		for (int i = 0; i < 5; i++) {

			DrawCircle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f)), HEIGHT - 1.2f * OFFSET, FONTSIZE, LIGHTGRAY);
			DrawCircle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f)), HEIGHT - 1.2f * OFFSET, FONTSIZE/1.3f, BLACK);
			DrawText(to_string(i + 1).c_str(), WIDTH / 10.0f + (i) * (WIDTH / (5.0f))-MeasureText(to_string(i + 1).c_str(), FONTSIZE)/2.0f, HEIGHT - 1.2f * OFFSET-FONTSIZE/2.0f, FONTSIZE, LIGHTGRAY);
			DrawRectangle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f))- OFFSET, HEIGHT - 0.8f * OFFSET,2*OFFSET,OFFSET/5.0f,LIGHTGRAY);
			DrawRectangle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f)) - OFFSET*0.95f, HEIGHT - 0.75f * OFFSET, 2 * OFFSET*0.95f, (OFFSET / 5.0f) * 0.475f, BLACK);
		}

		EndDrawing();
	}

	CloseWindow();


	return 0;
}

