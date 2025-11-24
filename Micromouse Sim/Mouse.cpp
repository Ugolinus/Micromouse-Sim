#include "Header.h"


Mouse::Mouse(Color col, int numberOfFieldsSQR, int sizeGameField, float sizeQuadrant, vector<bool> myLabyrinth, Shader& sh)
{
    this->col = col;
    this->numberOfFieldsSQR = numberOfFieldsSQR;
    this->sizeGameField = sizeGameField;
    this->sizeQuadrant = sizeQuadrant;

    this->pos = 1;
    this->myLabyrinth = myLabyrinth;

    this->orientation = DOWN;

    //Startposiition
    posVec = { 0,sizeQuadrant / 2.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    nowPos = posVec;


    this->model = LoadModelFromMesh(GenMeshSphere((float)sizeQuadrant / 3.0f, 20, 20));

    Image img = GenImageColor(10, 10, RED);
    this->tex = LoadTextureFromImage(img);
    UnloadImage(img);
    this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tex;
    this->model.materials[0].shader = sh;


}

Direction Mouse::mouseBrain()
{
    Direction direction;

    direction = (Direction)GetRandomValue(-2, 2);
   cout <<"Student: "<< direction << endl;
   return direction;
 
}

vector<int> Mouse::getSensorData()
{
    return vector<int>();
}

bool Mouse::makeMove(Direction dir)
{
    int posOld = pos;
    int row = pos / numberOfFieldsSQR;
    int col = pos % numberOfFieldsSQR;


    //Übersetzen von Angebener Richtung in globale Richtung über Ausrichtung
    if (orientation == DOWN)
        dir = (Direction)((int)dir* - 1);
    else if (orientation == RIGHT) {
        if((int)dir%2==0)
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

    cout << "Orient: "<<orientation<<endl<<"Real: "<<dir << endl<<endl;

    switch (dir) {
    case RIGHT: // rechts
        if (col < numberOfFieldsSQR - 1&& !myLabyrinth[pos+1]) { // nicht am rechten Rand
            pos++;
            orientation = RIGHT;
            return true;
        }
        break;

    case LEFT: // links
        if (col > 0 && !myLabyrinth[pos - 1]) { // nicht am linken Rand
            pos--;
            orientation = LEFT;
            return true;
        }
        break;

    case DOWN: // runter
        if (row < numberOfFieldsSQR - 1 && !myLabyrinth[pos + numberOfFieldsSQR]) { // nicht in der letzten Reihe
            pos += numberOfFieldsSQR;
            orientation = DOWN;
            return true;
        }
        break;

    case UP: // hoch
        if (row > 0 && !myLabyrinth[pos - numberOfFieldsSQR]) { // nicht in der ersten Reihe
            pos -= numberOfFieldsSQR;
            orientation = UP;
            return true;
        }
        break;
    }

    return false; // Bewegung nicht erlaubt

    if (pos<0 || pos>numberOfFieldsSQR * numberOfFieldsSQR)
        pos = posOld;

    

    return false;

}

void Mouse::draw(Shader& sh)
{
    //Soll Position wird gesetzt
    posVec = { 0,sizeQuadrant / 2.0f,0 };
    posVec.x = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos % numberOfFieldsSQR);
    posVec.z = (-numberOfFieldsSQR + 1) / 2.0f * sizeQuadrant + sizeQuadrant * (pos / numberOfFieldsSQR);

    nowPos.x += (posVec.x - nowPos.x)/30.0f;
    nowPos.z += (posVec.z - nowPos.z)/30.0f;

    //DrawSphere(nowPos, sizeQuadrant/2.5f, col);
    DrawModel(model, nowPos, 1.0f, RAYWHITE);
}

void update() {};

void Mouse::unload()
{
    UnloadModel(model);
    UnloadTexture(tex);
}