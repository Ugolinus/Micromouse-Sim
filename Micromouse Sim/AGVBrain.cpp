#include "AGVBrain.h"
#include "algorithm"

Direction AGVBrain::makeMove()
{
    translateSensoryDataIntoMap();

    Direction move;

    bool foundMove = false;

    fillValueMatrix();


    while (true) {
        move = calculateMove();

        if (brainLabyrinth[pos] == SUBGOAL) {
            currentGoal = GOAL;
        }
        else if (pos == 1 || brainLabyrinth[pos] == GOAL)
            currentGoal = SUBGOAL;
    

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

    if (brainLabyrinth[pos] == SUBGOAL) {
        currentGoal = GOAL;
    }
    else if (pos == 1 || brainLabyrinth[pos] == GOAL)
        currentGoal = SUBGOAL;

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

	//direction = (Direction)GetRandomValue(-2, 2);
	

    int indexU = pos - size;
    int indexD = pos + size;
    int indexR = pos + 1;
    int indexL = pos - 1;

    int valueU = 999;
    int valueD = 999;
    int valueR = 999;
    int valueL = 999;

    //Falls index exestiert und vergebene Nummer ist
    if (indexU >= 0 && indexU < wayValueMatrix.size() && wayValueMatrix[indexU] != -1) {

        valueU = wayValueMatrix[indexU];
    }

     if (indexD >= 0 && indexD < wayValueMatrix.size() && wayValueMatrix[indexD] != -1) {

         valueD = wayValueMatrix[indexD];
    }

     if (indexR >= 0 && indexR < wayValueMatrix.size() && wayValueMatrix[indexR] != -1) {

         valueR = wayValueMatrix[indexR];
    }

     if (indexL >= 0 && indexL < wayValueMatrix.size() && wayValueMatrix[indexL] != -1) {

         valueL = wayValueMatrix[indexL];
    }


     
      int minValue=(min(min(valueU, valueD), min(valueR, valueL)));
      if (valueU == minValue)
          direction = UP;
      else if (valueD == minValue)
          direction = DOWN;
      else if (valueL == minValue)
          direction = LEFT;
      else if (valueR == minValue)
          direction = RIGHT;

      
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

void AGVBrain::fillValueMatrix()
{

    int counter = 0;

    

    //Resetet Matrix
    for (int i = 0; i < brainLabyrinth.size(); i++) {
        if(brainLabyrinth[i]==BLOCK)
        wayValueMatrix[i] = -1;
        else if(brainLabyrinth[i] == currentGoal)
            wayValueMatrix[i] = 0;
        else 
            wayValueMatrix[i] = 9999;
    }

    bool allValuesGiven = true;

    while (true) {
        allValuesGiven = true;
        //Überprüfung das alle Werte vergeben sind
        for (int i = 0; i < wayValueMatrix.size(); i++) {
            if (wayValueMatrix[i] == 9999) {
                allValuesGiven = false;
                break;
            }
        }
        if (allValuesGiven) break;
        counter++;
        for (int i = 0; i < wayValueMatrix.size(); i++) {
            int indexU = i - size;
            int indexD = i + size;
            int indexR = i + 1;
            int indexL = i - 1;


            int row = pos / size;
            int col = pos % size;

            //Eckpunkte absichern
         


            int stopsCounter = 4;
           if (wayValueMatrix[i] == 9999) {
                if (i >= size) {
                   
                    if (wayValueMatrix[indexU] == -1)
                        stopsCounter--;
                }
                else
                    stopsCounter--;

                if (i + size < wayValueMatrix.size()) {
                   
                    if (wayValueMatrix[indexD] == -1)
                        stopsCounter--;
                }
                else
                    stopsCounter--;

                if (i % size != size - 1) {
                   

                    if (wayValueMatrix[indexR] == -1)
                        stopsCounter--;
                }
                else
                    stopsCounter--;

                if (i % size != 0) {
                    

                    if (wayValueMatrix[indexL] == -1)
                        stopsCounter--;
                }
                else
                    stopsCounter--;

                if (stopsCounter <= 0) {
                    brainLabyrinth[i] = BLOCK;
                    wayValueMatrix[i] = -1;
                }
            }
            //Falls Value bekannt ist
            if (wayValueMatrix[i] != 9999 && wayValueMatrix[i] != -1) {
                

                


                //Falls index exestiert und vergebene Nummer ist
                if (i >= size && wayValueMatrix[indexU] == 9999) {
                    wayValueMatrix[indexU] = wayValueMatrix[i] + 1;
                }
                else if (i + size < wayValueMatrix.size() && wayValueMatrix[indexD] == 9999) {
                    wayValueMatrix[indexD] = wayValueMatrix[i] + 1;
                }
                else if (i % size != size - 1 && wayValueMatrix[indexR] == 9999) {
                    wayValueMatrix[indexR] = wayValueMatrix[i] + 1;
                }
                else if (i % size != 0 && wayValueMatrix[indexL] == 9999) {
                    wayValueMatrix[indexL] = wayValueMatrix[i] + 1;
                }


            }
        }

        if (counter > 200) {
            for (int i = 0; i < wayValueMatrix.size(); i++) {
                if (wayValueMatrix[i] == 9999) {
                    wayValueMatrix[i] = -1;
                    brainLabyrinth[i] = BLOCK;
                }
            }
        }
    }
    
    
    


}

