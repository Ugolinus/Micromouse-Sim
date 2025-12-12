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

enum Objek {
	BLOCK = 0,
	GOAL = 3,
	SUBGOAL = 2,
	FREE = 1
};

void startRaylib();

