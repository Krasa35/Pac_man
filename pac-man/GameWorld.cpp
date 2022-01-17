#include "GameWorld.h"
#include <iostream>

#define BUILD(number, a1, a2, a3, a4, a5, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, height)\
	std::vector<Bound*> number##Row;\
 	for (int i = 0; i < gridLength; i++)	\
	{\
	if (i == 0 || i == 26 || i == a1 || i == a2 || i == a3 || i == a4 || i == a5) number##Row.push_back(new Bound(25.f + i * 25.f, height, "assets/png/line.png", true, false));\
	else if (i == gridLength - a1-1 || i == gridLength - a2-1 || i == gridLength - a3-1 || i == gridLength - a4-1 || i == gridLength - a5-1) number##Row.push_back(new Bound(25.f + i * 25.f, height, "assets/png/line.png", true, false));\
	else if (i == b1 || i == b2 || i == b3 || i == b4 || i == b5 || i == b6 || i == b7 || i == b8 || i == b9) number##Row.push_back(new Bound(25.f + i * 25.f, height, "assets/png/line.png", false, false));\
	else if (i == gridLength - b1-1 || i == gridLength - b2-1 || i == gridLength - b3-1 || i == gridLength - b4-1 || i == gridLength - b5-1 || i == gridLength - b6-1 || i == gridLength - b7-1 || i == gridLength - b8-1 || i == gridLength - b9-1 || i == gridLength - b10-1) number##Row.push_back(new Bound(25.f + i * 25.f, height, "assets/png/line.png", false, false));\
	else number##Row.push_back(new Bound(25.f + i * 25.f, height));\
	}\
	tiles.push_back(number##Row);

//----------------------------------------------------------------------------------//
GameWorld::GameWorld()
{
	this->setUpMap();
}

//DEKLARACJA KA¯DEGO Z RZÊDÓW - TWORZENIE KLASY Z GOTOWYMI DO WYRYSOWANIA OBIEKTAMI
void GameWorld::setUpMap(){
	this->tiles.clear();
	

	//first row
	std::vector<Bound*> firstRow;
	for(int i = 0; i < gridLength;i++)
		firstRow.push_back(new Bound(25.f + i*25.f, 25.f, "assets/png/line.png", false, false));
	tiles.push_back(firstRow);


	//second row
		BUILD(second, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50.f)
	
	//third row
		BUILD(third, 13, 0, 0, 0, 0, 2, 3, 4, 5, 7, 8, 9, 10, 11, 2, 75.f)

	//fourth row
		BUILD(fourth, 13, 2, 5, 7, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100.f)
	
	//fifth row
		BUILD(fifth, 13, 0, 0, 0, 0, 2, 3, 4, 5, 7, 8, 9, 10, 11, 2, 125.f)

	//sixth row
		BUILD(sixth, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150.f)

	//seventh row
		BUILD(seventh, 0, 0, 0, 0, 0, 2, 3, 4, 5, 7, 8, 10, 11, 12, 13, 175.f)	

	//eigth row
		BUILD(eigth, 0, 0, 0, 0, 0, 2, 3, 4, 5, 7, 8, 10, 11, 12, 13, 200.f)
	
	//ninth row
		BUILD(ninth, 7, 8, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 225.f)

	//tenth row
		BUILD(tenth, 7, 8, 13, 0, 0, 1, 2, 3, 4, 5, 9, 10, 11, 0, 0, 250.f)

	//eleventh row
		BUILD(eleventh, 7, 8, 0, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 275.f)

	//twelth row
		BUILD(twelth, 7, 8, 0, 0, 0, 1, 2, 3, 4, 5, 10, 11, 12, 0, 0, 300.f)

	//thirteenth row
		BUILD(thirteenth, 0, 0, 10, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 325.f)

	//fourteenth row
		BUILD(fourteenth, 7, 8, 0, 0, 0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 0, 350.f)

	//fifteenth row
		BUILD(fifteenth, 7, 8, 0, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 375.f)

	//sixteenth row
		BUILD(sixteenth, 0, 0, 0, 1, 0, 2, 3, 4, 5, 7, 8, 10, 11, 12, 13, 400.f)

	//seventeenth row
		BUILD(seventeenth, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 425.f)

	//eigthteenth row
		BUILD(eigthteenth, 13, 0, 0, 0, 0, 2, 3, 4, 5, 7, 8, 9, 10, 11, 2, 450.f)

	//nineteenth row
		BUILD(nineteenth, 13, 0, 0, 0, 0, 2, 3, 4, 5, 7, 8, 9, 10, 11, 2, 475.f)

	//twentieth row
		BUILD(twentieth, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 500.f)

	//twentyfirst row
		BUILD(twentyfirst, 4, 5, 1, 2, 7, 8, 10, 11, 12, 13, 0, 0, 0, 0, 0, 525.f)

	//twentysecond row
		BUILD(twentysecond, 13, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 0, 0, 0, 550.f)

	//twentythird row
		BUILD(twentythird, 13, 11, 0, 0, 0, 2, 3, 4, 5, 7, 8, 6, 9, 10, 0, 575.f)

	//twentyfourth row
		BUILD(twentyfourth, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600.f)

	//last row
		BUILD(last, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 0, 625.f)
}