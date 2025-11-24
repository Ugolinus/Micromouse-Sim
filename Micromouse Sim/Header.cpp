#include "Header.h"

void startRaylib()
{
	//Abfrage für Bildschirmgröße
	int h, w;

	system("cls");
	cout << "\n\n\n\t\tAGV SIMULATOR \n\t\tTU BERLIN\n\n\t\tIndustrielle Informationstechnik - Einfuhrung in die Informationstechnik fur Ingenieur:innen\n";
	cout << "\n\t\tPlease enter window pixel width: ";
	//cin >> w;
	cout << "\t\tPlease enter window pixel height: ";
	//cin >> h;

	const int HEIGHT = 2000;
	const int WIDTH = 3000;

	InitWindow(WIDTH, HEIGHT, "AGV SIMULATOR");
}
