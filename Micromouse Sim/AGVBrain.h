#pragma once
#include"Header.h"

class AGVBrain {

public:
	AGVBrain(vector<Objekt>&  brainLabyrinth, int startPos, Direction orientation) {
		this->brainLabyrinth = brainLabyrinth;
		this->orientation = orientation;
		this->pos = startPos;

		getDimensions();
	}

	Direction makeMove();
	
	//Up Rechts Links
	vector<bool> sensorInformation;
	
	vector<Objekt> brainLabyrinth;

	int pos;
	Direction orientation;
private:
	
	void translateSensoryDataIntoMap();

	Direction localToGlobal(Direction newMove);

	Direction calculateMove();

	void getDimensions();

	
	

	int size;

	bool sensorUp, sensorRight, sensorLeft;

	Direction globalToLocal(Direction dir);
};