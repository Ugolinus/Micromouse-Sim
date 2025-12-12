#pragma once
#include"Header.h"

class AGVBrain {

public:
	AGVBrain(vector<Objek>  brainLabyrinth) {
		this->brainLabyrinth = brainLabyrinth;
	}
	Direction makeMove();
	vector<bool> sensorInformation;
	vector<Objek> brainLabyrinth;
private:
	



};