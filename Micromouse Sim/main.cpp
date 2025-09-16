#include"Header.h"

int main() {

	InitWindow(1500, 1000, "Micromouse Simulator");
	Cam myCamera;

	SetTargetFPS(60);


	Labyrinth myLaby(30);
	Mouse myMouse(PINK,myLaby.numberOfFieldsSQR,myLaby.sizeGameField,myLaby.sizeQuadrant,myLaby.myLabyrinth);


	//Zeit controll
	float interval = 0.5f;
	float lastCall = 0.0;

	while (!WindowShouldClose()) {

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
		EndDrawing();
	}


	CloseWindow();


	return 0;
}

