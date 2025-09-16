#include "raylib.h"

int main() {

	InitWindow(1000, 1000, "Micromouse Simulator");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(BLACK);

		//Test 

		EndDrawing();
	}


	CloseWindow();


	return 0;
}

