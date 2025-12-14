#pragma once
#include"Header.h"
#include"Cam.h"
#include"Labyrinth.h"
#include"AGV.h"
#include"Run.h"
#include"AGVBrain.h"



class Simulation {
public:
	Simulation() : sh(LoadShader("min_light.vs", "min_light.fs"))
		, labyrinth(30, sh)
		, brain(map,1,DOWN)
		, mouse(PINK, labyrinth.numberOfFieldsSQR, labyrinth.sizeGameField,
			labyrinth.sizeQuadrant, labyrinth.myLabyrinth, sh) {



		//Shader
		// Uniform-Locations
		locLightPos = GetShaderLocation(sh, "uLightPos");
		locViewPos = GetShaderLocation(sh, "uViewPos");
		// Startposition des Lichts
		lightPos = { 0.0f, 20.5f, 0.0f };

		//Zeit Kontrolle
		interval = 0.0f;
		lastCall = 0.0;

		//Laden von Assets
		tu_logo = LoadTexture("TU_Logo.png");
		iit_logo = LoadTexture("IIT_Logo.png");
		arial = LoadFontEx("arial.ttf", 150, 0, 0);

		//Einstellungen des Fensters
		SetTextureFilter(arial.texture, TEXTURE_FILTER_BILINEAR);
		SetTargetFPS(60);


		//Knöpfe

		for (int i = 1; i < 4; i++) {
			runs.push_back(Run(i,100.0f,500.0f*i,300.0f,300.0f,3,&arial));
		}

		//Labyrinth bekommt Gehirn Map, startet mit Free

		for (int i = 0; i < labyrinth.myLabyrinth.size(); i++) {
			map.push_back(FREE);
		}

		this->brain=AGVBrain(map, 1, DOWN);
		labyrinth.p_brainLabyrinth = &brain.brainLabyrinth;
	
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

		for (int i = 0; i < runs.size(); i++) {
			if (runs[i].running)
				break;
			if (!runs[i].activated) {
				runs[i].isClicked();
			}
		}
		
		//AGV macht schritt
		for (int i = 0; i < runs.size(); i++) {
			reset();
			if (runs[i].running) {
				if (runs[i].stepsLeft == runs[i].stepsAllowed) {
					mouse.pos = 1;
					mouse.orientation = DOWN;
				}
				//Zeitsteuerung
				float t = GetTime();



				if (t - lastCall >= interval&& (mouse.nowPos.x== mouse.posVec.x) && (mouse.nowPos.z == mouse.posVec.z)) {
					
					while (!mouse.makeMove(brain.makeMove())) {
						
					}
					for (int i = 0; i < runs.size(); i++) {
						if (runs[i].running) {
							//Brain gets new sensor Data
							brain.sensorInformation = mouse.getSensorData();
							runs[i].update();
							break;
						}
					}
					lastCall = t;
				}
			}
		}

	}

	void draw() {
		BeginDrawing();


		BeginMode3D(myCamera.myCam);
		//DrawGrid(4, 10);

		ClearBackground(WHITE);

		mouse.draw(sh);
		labyrinth.draw(sh);
		

		EndMode3D();

		//Logo und Titel
		DrawTextEx(arial, "EII Projektaufgabe - Version 0.1", { (float)WIDTH-400,(float)HEIGHT - 30}, FONTSIZE / 2.0f, 1, BLACK);
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

		//Runs
		for (int i = 0; i < runs.size(); i++) {
			runs[i].draw();
		}

		//drawBrainInformation();

		EndDrawing();
	}


	void run() {
		while (!WindowShouldClose()) {



			update();

			draw();


		}

		end();
	}

	bool reset() {
		for (int i = 0; i < runs.size(); i++) {
			if (!runs[i].activated || runs[i].running) {
				return false;
			}
		}

		runs.clear();

		for (int i = 1; i < 4; i++) {
			runs.push_back(Run(i, 100.0f, 500.0f * i, 300.0f, 300.0f, 30, &arial));
		}

		//labyrinth=Labyrinth(30, sh,);
		//mouse=AGV(PINK, labyrinth.numberOfFieldsSQR, labyrinth.sizeGameField,
		//labyrinth.sizeQuadrant, labyrinth.myLabyrinth, sh);

		return true;
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
	AGV mouse;
	vector<Run> runs;
	AGVBrain brain;

	vector<Objekt> map;


	void drawBrainInformation() {

		Vector2 pos = { WIDTH - 3.5 * OFFSET ,OFFSET / 2.0f };

		DrawRectangle(pos.x, pos.y , 3 * OFFSET, 4 * OFFSET, DARKGRAY);
		DrawRectangle(pos.x+3, pos.y+3, 3 * OFFSET-6, 4 * OFFSET-6, WHITE);

		printArialText("Sensor Data: ", { pos.x + 10,pos.y + 10 }, 1.1);


	}

	void printArialText(string text, Vector2 pos, float size) {

		DrawTextEx(arial, text.c_str(), pos, (FONTSIZE / 2.0f)* size, 3, BLACK);

	}


};