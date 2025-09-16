#include "Header.h"

Labyrinth::Labyrinth(int size)
{

	this->sizeGameField = size;

	myLabyrinth = {

	1,0,1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,1,0,0,1,
	1,1,1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,1,0,1,1,
	1,0,1,1,1,0,1,0,0,1, 
	1,1,1,0,0,0,1,0,1,1, 
	1,0,0,0,1,1,1,0,0,1, 
	1,1,1,1,1,0,0,0,1,1, 
	1,1,0,0,0,0,1,0,0,1, 
	1,0,0,1,1,0,1,0,0,1, 
	1,1,1,1,1,1,1,1,1,1, 
	
	};
	this->numberOfFieldsSQR = sqrt(myLabyrinth.size());
	this->sizeQuadrant= sizeGameField / numberOfFieldsSQR;
}

void Labyrinth::draw()
{


	DrawPlane({}, {(float)sizeGameField,(float)sizeGameField  }, LIGHTGRAY);

	Vector3 pos = { -sizeQuadrant / 2.0f,sizeQuadrant/2.0f,-sizeQuadrant / 2.0f };
	
	for (int i = 0; i < myLabyrinth.size(); i++) {

		if (myLabyrinth[i]) {

			pos.x = (- numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant  + sizeQuadrant * (i%numberOfFieldsSQR);
			pos.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (i / numberOfFieldsSQR);

			DrawCube(pos, sizeQuadrant, sizeQuadrant/2.0f, sizeQuadrant, DARKGRAY);

		}
	}




}
