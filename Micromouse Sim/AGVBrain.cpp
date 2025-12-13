#include "AGVBrain.h"

Direction AGVBrain::makeMove()
{
	Direction move= calculateMove();

	


	return move;
}

void AGVBrain::translateSensoryDataIntoMap()
{



}

void AGVBrain::handleOrientation(Direction newMove)
{
    int posOld = pos;
    int row = pos / numberOfFieldsSQR;
    int col = pos % numberOfFieldsSQR;


    //Übersetzen von Angebener Richtung in globale Richtung über Ausrichtung
    if (orientation == DOWN)
        dir = (Direction)((int)dir * -1);
    else if (orientation == RIGHT) {
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / -2);
        else
            dir = (Direction)((int)dir * 2);
    }

    else if (orientation == LEFT) {
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / 2);
        else
            dir = (Direction)((int)dir * -2);
    }



}

Direction AGVBrain::calculateMove()
{
	Direction direction;

	direction = (Direction)GetRandomValue(-2, 2);
	cout << "Student: " << direction << endl;
	return direction;


}
