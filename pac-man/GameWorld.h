#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include <vector>

/*Klasa GameWorld - tworzy mape z obiektow klasy Bound za pomoc¹
* wektora wektorów wskaŸników na obiekty klasy Bound
*/
class GameWorld
{
private:
	void setUpMap();
public:
	std::vector< std::vector<Bound *> > tiles;
	int gridLength = 27;
	int gridHeight = 25;
	GameWorld();

};

