#include "Menu.h"
#include "Exception.h"

Exception* blad_m[2];
//konstruktor
Menu::Menu(float x, float y, std::string texture, float scale)
{
	if(!this->texture.loadFromFile(texture)) { blad_m[0] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/close_pac.png"); throw* blad_m[0]; }
	this->texture.setSmooth(true);
	sprite.setTexture(this->texture);
	sprite.scale(sf::Vector2f(scale, scale));
	sf::Vector2f multiplier{ (1.f / (2 * sprite.getScale().x)), (1.f / (2 * sprite.getScale().y)) };
	sprite.setOrigin(multiplier.x * sprite.getGlobalBounds().width, multiplier.y * sprite.getGlobalBounds().height);
	if (x > 900 || x < 0 || y > 700 || y < 0) { blad_m[1] = new Exception(4, "Pozycja przycisku nie znajduje sie w obrebie okna!"); throw* blad_m[1]; }
	sprite.setPosition(x, y);
}

//Zwraca Bounds poza klasa
sf::FloatRect Menu::getBounds()
{
	return sprite.getGlobalBounds();
}

//Ustaw pozycje utworzonego obiektu
void Menu::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

//draw
void Menu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}