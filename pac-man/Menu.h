#pragma once
#include <SFML/Graphics.hpp>

/*Klasa Menu - tworzy obiekty wizualne w menu
* 
* Wprowadza funkcje draw umozliwiaj¹c¹ wyrysowanie obiektu
*
*/
class Menu : public sf::Drawable
{
public:
	//metody
	Menu() = default;
	Menu(float x, float y, std::string texture, float scale);

	//metody get/set
	sf::FloatRect getBounds();
	void setPosition(sf::Vector2f position);

	//deklaracje
	sf::Sprite sprite;
	sf::Texture texture;

	//draw
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

