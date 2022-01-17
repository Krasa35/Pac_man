#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

/*Klasa Text - abstrakcyjna klasa ponad klasami: T_const i T_var
*
* Deklaruje metody wirtualne dla klas podrzêdnych
*
* Deklaruje nazwy robocze dla klas podrzêdnych
*
* Obsluguje metody get/set
*
* Wprowadza funkcje draw umozliwiaj¹c¹ wyrysowanie obiektu
*
*/
class Text : public sf::Drawable
{
public:
	//Deklaracje
	sf::Text text;
	sf::Font font;

	//metody get/set
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	//metody wirtualne
	virtual void update(int* score) = 0;
	virtual void update(std::string* display) = 0;
	
	//metoda draw
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

class T_const : public Text
{
public:
	T_const() = default;
	T_const(float x, float y, std::string napis, int size, std::string arg_font = "assets/ttf/crackman.ttf");
	void update(int* score) {};
	void update(std::string* display) {};
};

class T_var : public Text
{
private:
	std::stringstream ss;
public:
	T_var() = default;
	T_var(float x, float y, int size, std::string arg_font = "assets/ttf/crackman.ttf");
	void update(int* score);
	void update(std::string* display);
};

