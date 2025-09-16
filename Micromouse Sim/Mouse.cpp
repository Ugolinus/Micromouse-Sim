#include "Header.h"


Mouse::Mouse(Color col, int numberOfFieldsSQR, int sizeGameField, float sizeQuadrant)
{
    this->col = col;
    this->numberOfFieldsSQR = numberOfFieldsSQR;
    this->sizeGameField = sizeGameField;
    this->sizeQuadrant = sizeQuadrant;
}

int Mouse::mouseBrain()
{
    return 0;
}

vector<int> Mouse::getSensorData()
{
    return vector<int>();
}

void Mouse::makeMove(int direction)
{
}

void Mouse::draw()
{
    Vector3 posVec = { 0,sizeQuadrant/4.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    DrawSphere(posVec, sizeQuadrant/2.5f, col);
}

void update() {};

