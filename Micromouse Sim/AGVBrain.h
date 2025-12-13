#pragma once
#include"Header.h"

class AGVBrain {

public:
	AGVBrain(vector<Objekt>&  brainLabyrinth, int startPos, Direction orientation) {
		this->brainLabyrinth = brainLabyrinth;
		this->orientation = orientation;
		this->pos = startPos;
	}

	Direction makeMove();
	
	//Up Rechts Links
	vector<bool> sensorInformation;
	vector<Objekt> brainLabyrinth;
private:
	
	void translateSensoryDataIntoMap();

	void handleOrientation(Direction newMove);

	Direction calculateMove();

	Direction orientation;
	int pos;


};