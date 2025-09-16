#include "raylib.h"

int main() {

	InitWindow(1000, 1000, "Micromouse Simulator");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(BLACK);



		EndDrawing();
	}


	CloseWindow();


	return 0;
}

