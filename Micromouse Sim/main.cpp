#include "raylib.h"

int main() {

	InitWindow(1000, 1000, "Micromouse Simulator");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(BLACK);

		//Test 
		DrawCircle(500, 500, 100, RED);

		EndDrawing();
	}


	CloseWindow();


	return 0;
}

