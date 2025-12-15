#include "AGVBrain.h"

Direction AGVBrain::makeMove()
{
    translateSensoryDataIntoMap();

    Direction move;

    bool foundMove = false;

    while (true) {
        move = calculateMove();

       
    

        //Überprüfen dass Zug erlaubt ist 
        int indexUp = pos - size;
        int indexRight = pos + 1;
        int indexLeft = pos - 1;
        int indexDown = pos + size;

        switch (move) {
        case RIGHT: // rechts
            if (indexRight>=0&&indexRight< brainLabyrinth.size() && (brainLabyrinth)[indexRight] != BLOCK) {
                pos++;
                move = globalToLocal(move);
                orientation = RIGHT;
                foundMove = true;
            }
            break;

        case LEFT: // links
            if (indexLeft >= 0 && indexLeft < brainLabyrinth.size() && (brainLabyrinth)[indexLeft] != BLOCK) {
                pos--;
                move = globalToLocal(move);
                orientation = LEFT;
                foundMove = true;
            }
            break;

        case DOWN: // runter
            if (indexDown >= 0 && indexDown < brainLabyrinth.size() && (brainLabyrinth)[indexDown] != BLOCK) {
                pos += size;
                move = globalToLocal(move);
                orientation = DOWN;
                foundMove = true;
            }
            break;

        case UP: // hoch
            if (indexUp >= 0 && indexUp < brainLabyrinth.size() && (brainLabyrinth)[indexUp] != BLOCK) {
                pos -= size;
                move = globalToLocal(move);
                orientation = UP;
                foundMove = true;
            }
            break;
        }
        if (foundMove)
            break;
    }
    

    return move;
}

void AGVBrain::translateSensoryDataIntoMap()
{
    sensorUp=sensorInformation[0];
    sensorRight=sensorInformation[1];
    sensorLeft=sensorInformation[2];

    int indexUp = pos - size;
    int indexRight = pos + 1;
    int indexLeft = pos - 1;
    int indexDown = pos + size;
    vector<Direction> orientations = { localToGlobal(UP) ,localToGlobal(RIGHT), localToGlobal(LEFT) };
 

    for (int i = 0; i < sensorInformation.size(); i++) {

        if (sensorInformation[i]) {
            if (orientations[i] == UP) 
                brainLabyrinth[indexUp] = BLOCK;
             else if (orientations[i] == DOWN)
                brainLabyrinth[indexDown] = BLOCK;
             else if (orientations[i] == RIGHT)
                brainLabyrinth[indexRight] = BLOCK;
             else if (orientations[i] == LEFT)
                 brainLabyrinth[indexLeft] = BLOCK;
        }

    }
}

Direction AGVBrain::localToGlobal(Direction dir)
{

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

    return dir;

}

Direction AGVBrain::calculateMove()
{
	Direction direction;

	direction = (Direction)GetRandomValue(-2, 2);
	
    
      


	return direction;


}

void AGVBrain::getDimensions()
{
    size = sqrt(brainLabyrinth.size());

}

Direction AGVBrain::globalToLocal(Direction dir)
{
    if (orientation == DOWN) {
        dir = (Direction)((int)dir * -1);
    }
    else if (orientation == RIGHT) {
        // inverse von RIGHT ist LEFT-Logik
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / 2);
        else
            dir = (Direction)((int)dir * -2);
    }
    else if (orientation == LEFT) {
        // inverse von LEFT ist RIGHT-Logik
        if ((int)dir % 2 == 0)
            dir = (Direction)((int)dir / -2);
        else
            dir = (Direction)((int)dir * 2);
    }

    return dir;
}
