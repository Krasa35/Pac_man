///////////////////////////////////////////PAC-MAN/////////////////////////////////////////////////////////
/*Program korzysta z nastêpuj¹cych plików nag³ówkowych:
* 
* plik "Character.h" zawiera klasê abstrakcyjn¹ Character oraz klasy pochodne: Pac_man, Ghost, ...
*
* plik "Exception.h" klasa odpowiadaj¹ca za obiekty b³êdów
*
* plik "GameWorld.h" tworzy mapê gry z obiektów klasy Bound z pliku "Bound.h"
* 
* plik "funkcje.h" zawiera funkcje draw(<args>), collision(<args>), oraz cr_menu(<args>)
* 
* plik "Text.h" klasa odpowiadaj¹ca za tworzenie obiektów tekstowych w ca³ym pliku
* 
* plik "Menu.h" klasa odpowiadaj¹ca za tworzenie obiektów w menu (logo, przyciski...)
* 
*/
//-------------------------------------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Exception.h"
#include "GameWorld.h"
#include "funkcje.h"
#include "Text.h"
#include "Menu.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>

//--------------------------------------------------------------------//
//-----------------------------MAIN-----------------------------------//
//--------------------------------------------------------------------//
int main()
{
    //-----------------------------DEKLARACJE---------------------------//
    sf::RenderWindow window(sf::VideoMode(900, 700), "PAC-MAN wersja uposledzona");
    window.setFramerateLimit(144);

    //TWORZENIE OBIEKTÓW KLAS DO MENU
    Menu* m_logo = new Menu;
    Menu* m_play = new Menu;
    Menu* m_about = new Menu;
    Menu* m_exit = new Menu;
    Menu* m_back = new Menu;
    Menu* m_typebox = new Menu;

    Text* t_about = new T_const;
    Text* t_com = new T_const;
    Text* t_nick = new T_var;
    Text* t_rankw[5];
    Text* t_rankn[5];
    Text* textcg = new T_const;
    Text* textcl = new T_const;
    Text* textv = new T_var;

    GameWorld* g_gamemap = new GameWorld;                                                                                   //Mapa
    Character* c_pac = new Pac_man;                                                                                         //Pac-man
    std::vector<Character*> c_ghost;                                                                                        //Duchy
    int ghostNo = 4;
    std::vector<Menu*> m_pac_lives;                                                                                         //ilosc zyc - pacmany
    std::vector<Bound*> fruit;

    try
    {
        //-------------------------------------------------TEXT----------------------------------------------//
        t_about = new T_const(170.f, 100.f, "ORIGINAL ARCADE:\n\nNAMCO (C) 1980 \n\n\nSOURCE OF INSPIRATION:\n\nhttps://pacman.live \n\n\nREMAKE:\n\nKACPER KRASINSKI", 30, "assets/ttf/menu.ttf");
        t_com = new T_const(50.f, 285.f, "NICK: ", 30, "assets/ttf/menu.ttf");
        t_nick = new T_var(250.f, 285.f, 30, "assets/ttf/menu.ttf");
        for (int i = 0; i < 5; i++) {
            t_rankw[i] = new T_var(200.f, 300.f + 50.f * i, 30, "assets/ttf/menu.ttf");
            t_rankn[i] = new T_var(300.f, 300.f + 50.f * i, 30, "assets/ttf/menu.ttf");
        }
        textcg = new T_const(700.f, 25.f, "SCORE: \n\n LIVES : ", 50);                                                  //Tekst  //cg - const in game
        textcl = new T_const(200.f, 170.f, "YOUR SCORE:\n\n\tTOP SCORES:", 30, "assets/ttf/menu.ttf");                  //Tekst  //cl - const in lost
        textv = new T_var(750.f, 70.f, 50);
        //-------------------------------------------------Character-----------------------------------------//
        GameWorld* g_gamemap = new GameWorld;                                                                        //Mapa
        c_pac = new Pac_man;                                                                                         //Pac-man
        for (int i = 0; i < ghostNo; i++) {
            c_ghost.push_back(new Ghost(i));
        }
        //-------------------------------------------------Menu----------------------------------------------//
        for (int i = 0; i < 3; i++) {
            m_pac_lives.push_back(new Menu(750.f + 50.f * i, 250.f, "assets/png/open_pac.png", 0.1));
        }
        //-------------------------------------------------Owoce---------------------------------------------//
        for (int i = 0; i < 4; i++)
        {
            if (i < 2) { fruit.push_back(new Bound(42.5, 90.f + i * 400.f)); }
            else { fruit.push_back(new Bound(642.5, 90.f + (i - 2) * 400.f)); }
            fruit[i]->setSize(10.f);
            fruit[i]->setBlue();
        }
        //-------------------------------------------------BUTTONS---------------------------------------------//
        m_logo = new Menu(450.f, 100.f, "assets/png/logo.png", 0.4);
        m_play = new Menu(450.f, 400.f, "assets/png/play.png", 1);
        m_about = new Menu(450.f, 500.f, "assets/png/about.png", 1);
        m_exit = new Menu(450.f, 600.f, "assets/png/back.png", 1);
        m_back = new Menu(450.f, 600.f, "assets/png/back.png", 1);
        m_typebox = new Menu(450.f, 300.f, "assets/png/typebox.png", 1);
    }
    catch (Exception ex)
    {
        std::cout << ex;
    }

    //ZMIENNE GLOBALNE
    int score = 0;
    int bestscore = 0;
    int lives = 3;
    bool isMenu = true;
    bool isAbout = false;
    bool close = false;
    bool nothing = true;
    bool isPressed = false;
    std::string display;
    
    //Odczyt z pliku
    std::vector<Ranking*> ranking;
    file_op(true, display, bestscore, ranking);
        //------------------------TWORZENIE OKNA-----------------------------//
    while (window.isOpen())
    {
         sf::Event event;
         while (window.pollEvent(event))
            {
             if (event.type == sf::Event::Closed)
             {
                 window.close();
                 goto close;
             }
             type_nick(event, window, m_typebox->sprite, display, &isPressed, &isMenu);
            }
        //--------------------------------------------------------------------//
        //-----------------------MENU + WYJSCIE-------------------------------//
        //--------------------------------------------------------------------//
         if (isMenu && !isAbout)
         {
             window.clear({ 62, 62, 62 });
             lives = 3;
             textv->setPosition({ 780.f, 75.f });
             cr_menu(window, &isMenu, m_play->sprite, &isPressed);
             cr_menu(window, &isAbout, m_about->sprite, &isPressed);
             cr_menu(window, &close, m_exit->sprite, &isPressed);
             cr_menu(window, &nothing, m_typebox->sprite, &isPressed);
             window.draw(*m_logo);
             window.draw(*m_play);
             window.draw(*m_about);
             window.draw(*m_exit);
             window.draw(*m_typebox);
             t_nick->update(&display);
             window.draw(*t_nick);
             window.draw(*t_com);
             window.display();
             //-----------------------------EXIT-----------------------------//
             if (close)
             {
                 goto close;
             }
         } 
         //-----------------------------ABOUT-----------------------------//
         else if (isAbout)
         {
             window.clear({ 62, 62, 62 });
             cr_menu(window, &isAbout, m_back->sprite, &isPressed);
             window.draw(*t_about);
             window.draw(*m_back);
             window.display();
         }
        //--------------------------------------------------------------------//
        //-----------------------------GRA------------------------------------//
        //--------------------------------------------------------------------//
        else if (lives > 0 && !isMenu)
        {
            window.clear();

            //-----------------------------UPDATE------------------------------//
            c_pac->update();
            for (int i = 0; i < ghostNo; i++) {
                c_ghost[i]->update(c_pac, i);
            }
            //w_ghost->update(w_pac);
            textv->update(&score);

            //-----------------------------DRAW-------------------------------//
            draw(g_gamemap, window);
            for (int i = 0; i < 4; i++) {
                window.draw(fruit[i]->shape);
            }
            window.draw(*c_pac);
            for (int i = 0; i < ghostNo; i++) {
                window.draw(c_ghost[i]->sprite);
            }
            window.draw(*textcg);
            window.draw(*textv);
            for (int i = 0; i < lives; i++) {
                window.draw(m_pac_lives[i]->sprite);
            }
            

            //-----------------------------KOLIZJE-----------------------------//
            collision(g_gamemap, c_pac, c_ghost, &score, ghostNo, &lives, fruit);


            window.display();
        }
        //--------------------------------------------------------------------//
        //----------------------PRZEGRALES + RANKING--------------------------//
        //--------------------------------------------------------------------//
        else if (lives <= 0 && !isMenu)
        {
             if (score > bestscore) { bestscore = score; }
            score = 0;
            window.clear({ 62, 62, 62 });
            window.draw(*m_logo);
            textv->setPosition({ 700.f, 155.f });
            for (int i = 0; i < 5; i++) {
                t_rankw[i]->update(&ranking[i]->wynik);
                t_rankn[i]->update(&ranking[i]->nick);
                window.draw(*t_rankw[i]);
                window.draw(*t_rankn[i]);
            }
            cr_menu(window, &isMenu, m_back->sprite, &isPressed);
            window.draw(*m_back);
            window.draw(*textv);
            window.draw(*textcl);
            window.display();
        }
    }
close:
    //zapis do pliku
    file_op(false, display, bestscore, ranking);
    return 0;
}
