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

enum Objekt {
	BLOCK = 0,
	GOAL = 3,
	SUBGOAL = 2,
	FREE = 1
};

void startRaylib();

struct Goal {

	bool mainGoal;
	bool activated;
	int pos;

};

const int HEIGHT = 1000;
const int WIDTH = HEIGHT*1.6;
const int OFFSET = WIDTH/20;
const int FONTSIZE = OFFSET/2.5;