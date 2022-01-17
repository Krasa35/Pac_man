#include "Text.h"
#include "Exception.h"

Exception* blad_t[4];
//------------------------TEXT--------------------//
//draw
void Text::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->text, state);
}

//zwraca Position poza klasa
sf::Vector2f Text::getPosition()
{
    return text.getPosition();
}

void Text::setPosition(sf::Vector2f position)
{
    text.setPosition(position);
}
//------------------------T_CONST--------------------//
//konstruktor
T_const::T_const(float x, float y, std::string napis, int size, std::string arg_font)
{
    if (!font.loadFromFile(arg_font)) { blad_t[0] = new Exception(1, "Nie udalo sie wczytac czcionki z pliku: " + arg_font); throw * blad_t[0]; };
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    if (x > 900 || x < 0 || y > 700 || y < 0) { blad_t[1] = new Exception(2, "Pozycja tekstu nie znajduje sie w obrebie okna!"); throw* blad_t[1]; }
    text.setPosition(x, y);
    text.setCharacterSize(size);
    text.setString(napis);
}

//------------------------T_VAR--------------------//
//konstruktor
T_var::T_var(float x, float y, int size, std::string arg_font)
{
    if (!font.loadFromFile(arg_font)) { blad_t[2] = new Exception(1, "Nie udalo sie wczytac czcionki z pliku: " + arg_font); throw* blad_t[2]; };
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    if (x > 900 || x < 0 || y > 700 || y < 0) { blad_t[3] = new Exception(2, "Pozycja tekstu nie znajduje sie w obrebie okna!"); throw* blad_t[3]; }
    text.setPosition(x, y);
    text.setCharacterSize(size);
}

//zmiana tekstu - update
void T_var::update(int* score)
{
    ss.str("");
    ss << *score;
    text.setString(ss.str());
}

void T_var::update(std::string *display)
{
    ss.str("");
    ss << *display;
    text.setString(ss.str());
}