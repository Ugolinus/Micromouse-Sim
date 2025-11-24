#include "Header.h"

Labyrinth::Labyrinth(int size, Shader& sh)
{

	this->sizeGameField = size;

	myLabyrinth = {

	1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,
	1,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,
	1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,1,
	1,0,0,1,0,0,0,1,1,0,1,0,1,1,0,1,
	1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,
	1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,
	1,1,0,1,0,1,1,0,0,1,0,0,1,1,1,1,
	1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,
	1,1,0,1,1,1,1,0,1,1,0,0,1,0,1,1,
	1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,
	1,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,
	1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,0,1,0,1,0,1,1,0,1,
	1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	this->numberOfFieldsSQR = sqrt(myLabyrinth.size());
	this->sizeQuadrant= (float)sizeGameField / numberOfFieldsSQR;

	//Shader
	Mesh m = GenMeshCube(sizeQuadrant, sizeQuadrant / 2.0f, sizeQuadrant);
	this->model = LoadModelFromMesh(m);

	Image img = GenImageColor(10,10, DARKGRAY);
	this->tex = LoadTextureFromImage(img);
	UnloadImage(img);
	this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tex;

	this->model.materials[0].shader = sh;

	//Floor
	Image img_ground = GenImageColor(10, 10, GRAY);
	this->tex_floor = LoadTextureFromImage(img_ground);

	this->ground = LoadModelFromMesh(GenMeshPlane(sizeGameField, sizeGameField, 200, 200));
	ground.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tex_floor;
	ground.materials[0].shader = sh;
	UnloadImage(img_ground);

	//Goal
	Image img_ball = GenImageColor(10, 10, GOLD);
	this->ball_tex = LoadTextureFromImage(img_ball);

	this->ball = LoadModelFromMesh(GenMeshSphere(3.0f*(float)sizeQuadrant/4.0f,20,20));
	ball.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = ball_tex;
	ball.materials[0].shader = sh;
	UnloadImage(img_ball);
}

void Labyrinth::unload()
{
	UnloadModel(model);
	UnloadTexture(tex);
	UnloadTexture(tex_floor);
	UnloadModel(ground);

	UnloadModel(ball);
	UnloadTexture(ball_tex);
}

void Labyrinth::draw(Shader& sh)
{
	int locEmissive = GetShaderLocation(sh, "uEmissive");

	// Normale Flächen
	float off = 0.0f;

	//DrawPlane({}, {(float)sizeGameField,(float)sizeGameField  }, LIGHTGRAY);
	DrawModel(ground, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
	DrawModel(ball, { 0.0f, 0.0f, 0.0f }, 1.0f, RAYWHITE);
	//DrawSphere({0,sizeQuadrant/2,0 }, (float)sizeQuadrant/2, YELLOW);

	Vector3 pos = { -sizeQuadrant / 2.0f,sizeQuadrant/4.0f,-sizeQuadrant / 2.0f };
	
	for (int i = 0; i < myLabyrinth.size(); i++) {

		if (myLabyrinth[i]) {

			pos.x = (- numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant  + sizeQuadrant * (i%numberOfFieldsSQR);
			pos.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i / numberOfFieldsSQR);

			DrawModel(this->model, pos, 1, WHITE);
			//DrawCube(pos, sizeQuadrant, sizeQuadrant/2.0f, sizeQuadrant, DARKGRAY);
			//Oben
			//DrawPlane({ pos.x,pos.y+ sizeQuadrant / 4.0f,pos.z }, { sizeQuadrant,sizeQuadrant }, WHITE);
		}
	}




}
