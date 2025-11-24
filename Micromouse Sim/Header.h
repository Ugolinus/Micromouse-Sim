#pragma once

#include<raylib.h>
#include<raymath.h>
#include<vector>
#include<iostream>
#include <string>

#include<iostream>

using namespace std;


enum Direction {
	UP = 1,
	DOWN = -1,
	RIGHT = 2,  
	LEFT = -2   
};


class Cam {
public:
	Camera3D myCam;
	float R;
	const float R_MIN = 100.0f;
	const float R_MAX = 200.0f;
	float pitch;
	float yaw;
	const float PITCH_LIMIT_MAX = PI / 2 - 0.01f;
	const float PITCH_LIMIT_MIN = 0.5;

	Cam();

	void update();

};

class Labyrinth {
public:
	vector<bool> myLabyrinth;

	Labyrinth(int size, Shader& sh);

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;


	Model model;
	Model ground;
	Model ball;
	Texture2D ball_tex;
	Texture2D tex;
	Texture2D tex_floor;

	void unload();

	void draw(Shader& sh);

};

class Mouse {
public:
	vector<bool> myLabyrinth;
	Color col;
	int pos;

	Direction orientation;
	
	Vector3 posOnScreen;
	Vector3 posVec;
	Vector3 nowPos;
	Mouse(Color col, int numberOfFieldsSQR, int sizeGameField,float sizeQuadrant, vector<bool> myLabyrinth, Shader& sh);

	Direction mouseBrain();

	int numberOfFieldsSQR;
	int sizeGameField;
	float sizeQuadrant;
	vector<int> getSensorData();
	bool makeMove(Direction direction);

	Model model;
	Texture2D tex;

	void draw(Shader& sh);

	void unload();
};


class Simulation {
public:
	Simulation() : sh(LoadShader("min_light.vs", "min_light.fs"))             
		, labyrinth(30, sh)
		, mouse(PINK, labyrinth.numberOfFieldsSQR, labyrinth.sizeGameField,
			labyrinth.sizeQuadrant, labyrinth.myLabyrinth, sh) {



		//Shader
		// Uniform-Locations
		locLightPos = GetShaderLocation(sh, "uLightPos");
		locViewPos = GetShaderLocation(sh, "uViewPos");
		// Startposition des Lichts
		lightPos = { 0.0f, 20.5f, 0.0f };

		//Zeit Kontrolle
		 interval = 1.0f;
		 lastCall = 0.0;

		//Laden von Assets
		tu_logo = LoadTexture("TU_Logo.png");
		iit_logo = LoadTexture("IIT_Logo.png");
		arial = LoadFontEx("arial.ttf", 150, 0, 0);

		//Einstellungen des Fensters
		SetTextureFilter(arial.texture, TEXTURE_FILTER_BILINEAR);
		SetTargetFPS(60);

	}


	void end() {

		CloseWindow();

		UnloadFont(arial);
		UnloadTexture(tu_logo);
		UnloadTexture(iit_logo);
		UnloadShader(sh);
	}

	void update() {


		updateShaderAndCam();


		//Zeitsteuerung
		float t = GetTime();

		if (t - lastCall >= interval) {
			while (!mouse.makeMove(mouse.mouseBrain())) {
			};
			lastCall = t;
		}

	}

	void draw() {
		BeginDrawing();


		BeginMode3D(myCamera.myCam);
		//DrawGrid(4, 10);

		ClearBackground(WHITE);

		labyrinth.draw(sh);
		mouse.draw(sh);

		EndMode3D();

		//Logo und Titel

		DrawTextEx(arial, "AGV Simulator", { (float)tu_logo.width + iit_logo.width + 30,(float)tu_logo.height / 2 - 20 }, FONTSIZE, 5, BLACK);
		DrawTexture(tu_logo, 0, 0, WHITE);
		DrawTexture(iit_logo, tu_logo.width, 30, WHITE);
		/*DrawText("Micro Mouse Simulator", (WIDT
		H - MeasureText("Micro Mouse Simulator", FONTSIZE)) / 2.0f, OFFSET , FONTSIZE, LIGHTGRAY);
		DrawLineEx({ 0, HEIGHT - 2*OFFSET }, { WIDTH, HEIGHT - 2 * OFFSET },5, LIGHTGRAY);


		for (int i = 0; i < 5; i++) {

			DrawCircle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f)), HEIGHT - 1.2f * OFFSET, FONTSIZE, LIGHTGRAY);
			DrawCircle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f)), HEIGHT - 1.2f * OFFSET, FONTSIZE/1.3f, BLACK);
			DrawText(to_string(i + 1).c_str(), WIDTH / 10.0f + (i) * (WIDTH / (5.0f))-MeasureText(to_string(i + 1).c_str(), FONTSIZE)/2.0f, HEIGHT - 1.2f * OFFSET-FONTSIZE/2.0f, FONTSIZE, LIGHTGRAY);
			DrawRectangle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f))- OFFSET, HEIGHT - 0.8f * OFFSET,2*OFFSET,OFFSET/5.0f,LIGHTGRAY);
			DrawRectangle(WIDTH / 10.0f + (i) * (WIDTH / (5.0f)) - OFFSET*0.95f, HEIGHT - 0.75f * OFFSET, 2 * OFFSET*0.95f, (OFFSET / 5.0f) * 0.475f, BLACK);
		}*/

		EndDrawing();
	}


	void run() {
		while (!WindowShouldClose()) {



			update();

			draw();


		}

		end();
	}

	void updateShaderAndCam() {
		//Kamera
		myCamera.update();

		//SHADER
		SetShaderValue(sh, locLightPos, &lightPos, SHADER_UNIFORM_VEC3);
		SetShaderValue(sh, locViewPos, &myCamera.myCam.position, SHADER_UNIFORM_VEC3);
		locRangeScale = GetShaderLocation(sh, "uRangeScale");

		SetShaderValue(sh, locRangeScale, &rangeScale, SHADER_UNIFORM_FLOAT);
	}

private:
	Shader sh;
	int locLightPos;
	int locViewPos;
	Vector3 lightPos;
	float rangeScale = 0.1f; //  Reichweite vom Licht
	int locRangeScale;

	float interval = 0.5f;
	float lastCall = 0.0;

	const int HEIGHT = 2000;
	const int WIDTH = 3000;
	const int OFFSET = 150;
	const int FONTSIZE = 50;

	Texture2D  tu_logo;
	Texture2D  iit_logo;
	Font arial;

	Cam myCamera;

	//Objekte der Simulation
	Labyrinth labyrinth;
	Mouse mouse;
	

	

};

void startRaylib();