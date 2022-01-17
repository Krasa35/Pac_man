#pragma once
#include <SFML/Graphics.hpp>

/*Klasa Bound - klasa potrzebna klasie GameWorld do utworzenia mapy ze spritow
*
*Tworzy obiekty poprzez konstruktory za pomoca swoich metod
* 
* Deklaruje metode draw do rysowania spritow z GameWorld z Bound (*PATRZ "funkcje.h" draw //RYSOWANIE MAPY*)
*/
class Bound : public sf::Drawable
{
private:
    //Deklaracje robocze:
    sf::Texture texture;
    
    sf::Vector2f size = { 10,10 };
    sf::FloatRect scale = { 0,0,50,50 };

public:
    //Metody publiczne:
    Bound( float pos_x, float pos_y, std::string tex, bool isRotated, bool isPassable);
    Bound(float pos_x, float pos_y);

    //metody get/set
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    void setSize(int radius);
    void setBlue();

    //deklaracje
    sf::Sprite sprite;
    sf::CircleShape shape;

    //Funkcja draw:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};
