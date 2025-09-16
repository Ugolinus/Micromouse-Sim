#include"Header.h"

int main() {

	InitWindow(1000, 1000, "Micromouse Simulator");
	Cam myCamera;

	SetTargetFPS(60);


	Labyrinth myLaby(50);


	while (!WindowShouldClose()) {

		myCamera.update();

		BeginDrawing();

		BeginMode3D(myCamera.myCam);
		//DrawGrid(4, 10);
	
		ClearBackground(WHITE);

		//Test 

		myLaby.draw();
		

		EndMode3D();
		EndDrawing();
	}


	CloseWindow();


	return 0;
}

