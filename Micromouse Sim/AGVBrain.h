#pragma once
#include"Header.h"

class AGVBrain {

public:
	AGVBrain(vector<bool>  brainLabyrinth) {
		this->brainLabyrinth = brainLabyrinth;
	}
	Direction makeMove();
	vector<bool> sensorInformation;
	vector<bool> brainLabyrinth;
private:
	



};