#include"Header.h"

int main() {

	InitWindow(1500, 1500, "Micromouse Simulator");
	Cam myCamera;

	SetTargetFPS(60);


	Labyrinth myLaby(50);
	Mouse myMouse(RED,myLaby.numberOfFieldsSQR,myLaby.sizeGameField,myLaby.sizeQuadrant);

	while (!WindowShouldClose()) {

		//Update
		myCamera.update();
		myMouse.pos = 1;


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

