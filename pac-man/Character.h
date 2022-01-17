#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include "Bound.h"

/*Klasa Character - abstrakcyjna klasa ponad klasami: Pac_man, oraz Ghost
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
class Character : public sf::Drawable
{
public:
    //Metody publiczne:
    Character() {};

    //Metody wirtualne (musz¹ byæ ustawione na 0):
    virtual void update() = 0;
    virtual void update(Character *w_pac, int i) = 0;
    virtual void changeCollision(bool arg_isCollision) = 0;
    virtual void die() = 0;
    virtual void changeDeath(bool arg_isDead) = 0;
    bool isFizzy = false;
    bool isInvurnelable = false;

    //Deklaracje robocze:
    sf::Texture texture;
    sf::Texture texture2;
    sf::Texture brak;
    sf::Sprite sprite;
    sf::Clock timer;
    sf::Clock death_timer;
    sf::Clock timer_ghost;
    sf::Vector2f velocity{ 0.f, 0.f };

    //metody get/set
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();


    //Funkcja draw:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};

//------------------------------------------------//
//------------KLASY DZIEDZICZ¥CE------------------//
//------------------------------------------------//

class Pac_man : public Character
{
private:
    //Deklaracje
    sf::Clock timer;

    //Zmienne prywatne:
    const float Pac_manVelocity{ 1.f };
    sf::Vector2f lastVelocity{ 0.f, 0.f };
    sf::Vector2f position{ 350.f, 500.f };
    float rotation = 0;
    float lastRotation = 0;
    bool isDead = false;
    bool isCollision = false;

    //Metody prywatne:
    void setTexture();
    void setMove(char forbidden);
    void moveBack();
    void rotate();
    void move();
    void setPosition();

public:
    //Metody publiczne:
    Pac_man();
    void die();
    void update();
    void update(Character* w_pac, int i) {};
    void changeCollision(bool arg_isCollision);
    void changeDeath(bool arg_isDead) {};
};

class Ghost : public Character
{
private:

    //Zmienne prywatne:
    const float ghostVelocity{ 1.f };
    sf::Vector2f lastVelocity{ 0.f, 0.f };
    sf::Vector2f position{ 300.f, 325.f };
    sf::Vector2f lastPosition{ 0.f, 0.f };
    sf::Vector2f startPosition{ 0.f, 0.f };
    int bangNo = 0;
    int nr = 0;
    bool isCollision = false;
    bool isDead = false;
    bool isStuck = false;
    //bool isVelOver = false;                 //is velocity overwriten


    //Metody prywatne:
    void setsetMove(char dir);
    void setMove(sf::Vector2f togo);
    void moveBack();
    void move(sf::Vector2f togo);
    void setPosition();
    void bangSet();
    void fizzySet();
    float calc_dist(sf::Vector2f pac_pos, char dir);

public:
    //Deklaracje
    sf::Texture fizzy;

    //Metody publiczne:
    Ghost(int a);
    void die();
    void update() {};
    void update(Character* w_pac, int i);
    void changeCollision(bool arg_isCollision);
    void changeDeath(bool arg_isDead);
};