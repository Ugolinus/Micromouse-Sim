#include "Header.h"

int HEIGHT = 2000;
int WIDTH = 0;
int OFFSET = 0;
int FONTSIZE = 0;


void startRaylib()
{
	//Abfrage für Bildschirmgröße
	

	system("cls");
	cout << "\n\n\n\AGV SIMULATOR \nTU BERLIN\n\nIndustrielle Informationstechnik - Einfuhrung in die Informationstechnik fur Ingenieur:innen\n";
	
	cout << "\nPlease enter window pixel height:\n";
	int h;
	while (true) {
		if (std::cin >> h && h > 0) {
			HEIGHT = h;
			break;
		}
		std::cout << "Ungueltig. Bitte eine ganze Zahl > 0 eingeben: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	
	  WIDTH = HEIGHT * 1.6;
	  OFFSET = WIDTH / 20;
	  FONTSIZE = OFFSET / 2.5;

	InitWindow(WIDTH, HEIGHT, "AGV SIMULATOR");
}
