#include "Header.h"


Mouse::Mouse(Color col, int numberOfFieldsSQR, int sizeGameField, float sizeQuadrant, vector<bool> myLabyrinth)
{
    this->col = col;
    this->numberOfFieldsSQR = numberOfFieldsSQR;
    this->sizeGameField = sizeGameField;
    this->sizeQuadrant = sizeQuadrant;

    this->pos = 1;
    this->myLabyrinth = myLabyrinth;



    //Startposiition
    posVec = { 0,sizeQuadrant / 4.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    nowPos = posVec;
}

int Mouse::mouseBrain()
{

    while (true) {
        int direction = GetRandomValue(-2, 2);

        if (direction)
            return direction;
    }
}

vector<int> Mouse::getSensorData()
{
    return vector<int>();
}

bool Mouse::makeMove(int dir)
{
    

    int posOld = pos;
    int row = pos / numberOfFieldsSQR;
    int col = pos % numberOfFieldsSQR;

    switch (dir) {
    case 1: // rechts
        if (col < numberOfFieldsSQR - 1&& !myLabyrinth[pos+1]) { // nicht am rechten Rand
            pos++;
            return true;
        }
        break;

    case -1: // links
        if (col > 0 && !myLabyrinth[pos - 1]) { // nicht am linken Rand
            pos--;
            return true;
        }
        break;

    case 2: // runter
        if (row < numberOfFieldsSQR - 1 && !myLabyrinth[pos + numberOfFieldsSQR]) { // nicht in der letzten Reihe
            pos += numberOfFieldsSQR;
            return true;
        }
        break;

    case -2: // hoch
        if (row > 0 && !myLabyrinth[pos - numberOfFieldsSQR]) { // nicht in der ersten Reihe
            pos -= numberOfFieldsSQR;
            return true;
        }
        break;
    }

    return false; // Bewegung nicht erlaubt

    if (pos<0 || pos>numberOfFieldsSQR * numberOfFieldsSQR)
        pos = posOld;

    

    return false;

}

void Mouse::draw()
{
    //Soll Position wird gesetzt
    posVec = { 0,sizeQuadrant / 4.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    nowPos.x += (posVec.x - nowPos.x)/30.0f;
    nowPos.z += (posVec.z - nowPos.z)/30.0f;

    DrawSphere(nowPos, sizeQuadrant/2.5f, col);
}

void update() {};

