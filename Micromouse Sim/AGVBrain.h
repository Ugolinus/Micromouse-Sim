#pragma once
#include"Header.h"

class AGVBrain {

public:
	AGVBrain(vector<Objekt>&  brainLabyrinth, int startPos, Direction orientation) {
		this->brainLabyrinth = brainLabyrinth;
		this->orientation = orientation;
		this->pos = startPos;

		//Beim Inezieren muss es noch mit sinnvollen Werten gefüllt werden
		for (int i = 0; i < this->brainLabyrinth.size(); i++) {
			this->wayValueMatrix.push_back(0);
		}

		this->showWayValues = true;
		
		getDimensions();
		this->currentGoal = SUBGOAL;
		
	}

	Direction makeMove();
	
	//Up Rechts Links
	vector<bool> sensorInformation;
	
	vector<Objekt> brainLabyrinth;
	bool showWayValues;
	int pos;
	Direction orientation;

	vector<int> wayValueMatrix;
private:
	
	void translateSensoryDataIntoMap();

	Direction localToGlobal(Direction newMove);

	Direction calculateMove();

	void getDimensions();

	Objekt currentGoal;
	
	vector<int> wayValues;

	int size;

	bool sensorUp, sensorRight, sensorLeft;

	Direction globalToLocal(Direction dir);

	void fillValueMatrix();

	
	


};