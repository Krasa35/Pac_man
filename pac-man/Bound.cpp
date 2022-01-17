#include "Bound.h"
#include <iostream>
//------------------------------------------------//
//----------------METODY BOUND--------------------//
//------------------------------------------------//
void Bound::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}

//konstruktor - sciany
Bound::Bound(float pos_x, float pos_y, std::string tex, bool isRotated, bool isPassable)
{
	texture.loadFromFile(tex);				// throw wyjatek
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setPosition(pos_x, pos_y);
	sprite.setScale(0.05,0.05);			//szerokoœæ mniej wiêcej równa szerokoœci pac_mana
	sf::Vector2f multiplier{ (1.f / (2 * sprite.getScale().x)), (1.f / (2 * sprite.getScale().y)) };
	sprite.setOrigin(multiplier.x * sprite.getGlobalBounds().width, multiplier.y * sprite.getGlobalBounds().height);
	if (isRotated) sprite.setRotation(270);
}

//drugi konstruktor - kulki (punkty)
Bound::Bound(float pos_x, float pos_y)
{
	shape.setPosition(pos_x, pos_y);
	shape.setFillColor(sf::Color::Red);
	shape.setRadius(this->size.x / 3);
	shape.setOrigin(this->size.x / 3, this->size.y / 3);
}

//Zwraca Bounds poza klasa
sf::FloatRect Bound::getBounds()
{
	return sprite.getGlobalBounds();
}

void Bound::setSize(int radius)
{
	shape.setRadius(radius);
}

void Bound::setBlue()
{
	shape.setFillColor(sf::Color::Blue);
}

//Zwraca position poza klasa
sf::Vector2f Bound::getPosition()
{
	return this->sprite.getPosition();
}