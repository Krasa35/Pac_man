#pragma once
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdlib>

struct Ranking
{
public:
    int wynik;
    std::string nick;
    bool operator<=(int r1)
    {
        if (this->wynik <= r1) { return true; }
        else { return false; }
    }
};

//RYSOWANIE MAPY
void draw(GameWorld* gamemap, sf::RenderWindow& window) {
    for (int i = 0; i < gamemap->gridHeight; i++)
    {
        for (int j = 0; j < gamemap->gridLength; j++)
        {
            window.draw((gamemap->tiles[i][j])->sprite);
        }
    }

    for (int i = 0; i < gamemap->gridHeight; i++)
    {
        for (int j = 0; j < gamemap->gridLength; j++)
        {
            window.draw((gamemap->tiles[i][j])->shape);
        }
    }
}

//KOLIZJE
void collision(GameWorld* gamemap, Character* w_pac, std::vector<Character*> w_ghost, int* score, int ghostNo, int* lives, std::vector<Bound*> fruit)
{
    //OBS£UGA KOLIZJI (œciana - pac_man)
    for (int i = 0; i < gamemap->gridHeight; i++)
    {
        for (int j = 0; j < gamemap->gridLength; j++)
        {
            if (w_pac->getBounds().intersects(gamemap->tiles[i][j]->sprite.getGlobalBounds()))
            {
                w_pac->changeCollision(true);
                w_pac->update();
            }
        }
    }

    //OBS£UGA KOLIZJI (œciana - ghost)
    for (int i = 0; i < gamemap->gridHeight; i++)
    {
        for (int j = 0; j < gamemap->gridLength; j++)
        {
            for (int k = 0; k < ghostNo; k++)
            {
                if (w_ghost[k]->getBounds().intersects(gamemap->tiles[i][j]->sprite.getGlobalBounds()))
                {
                    w_ghost[k]->changeCollision(true);
                    w_ghost[k]->update();
                }
            }
        }
    }

    //OBSLUGA KOLIZJI (pac_man - ghost)
    for (int k = 0; k < ghostNo; k++)
    {
        if (w_ghost[k]->getBounds().intersects(w_pac->getBounds()) && !w_ghost[k]->isInvurnelable)
        {
            if (!w_ghost[k]->isFizzy)
            {
                w_pac->death_timer.restart();
                w_pac->die();
                for (int j = 0; j < ghostNo; j++)
                {
                    w_ghost[j]->death_timer.restart();
                    w_ghost[j]->die();
                }
                (*lives)--;
            }
            else
            {
                //w_ghost[k]->isInvurnelable = true;
                w_ghost[k]->isFizzy = false;
                w_ghost[k]->die();
                (*score) += 100;
            }
            
        }
    }

    //OBS£UGA KOLIZJI (point - pac_man) + RESET KULEK
    for (int i = 0; i < gamemap->gridHeight; i++)
    {
        for (int j = 0; j < gamemap->gridLength; j++)
        {
            if (w_pac->getBounds().intersects(gamemap->tiles[i][j]->shape.getGlobalBounds()))
            {
                if (gamemap->tiles[i][j]->shape.getFillColor() == sf::Color::Red)
                {
                    gamemap->tiles[i][j]->shape.setFillColor(sf::Color::Black);
                    (*score)++;
                    std::cout << *score << std::endl;
                }
            }
            //KOLOROWANIE PUNKTOW NA NOWO
            if (*lives == 0)
            {
                for (int i = 0; i < gamemap->gridHeight; i++)
                {
                    for (int j = 0; j < gamemap->gridLength; j++)
                    {
                        gamemap->tiles[i][j]->shape.setFillColor(sf::Color::Red);
                    }
                }
            }
        }
    }

    //OBS£UGA KOLIZJI (bigpoint - pac_man) + RESET KULEK
    for (int i = 0; i < fruit.size(); i++)
    {
        if (w_pac->getBounds().intersects(fruit[i]->shape.getGlobalBounds()))
         {
           if (fruit[i]->shape.getFillColor() == sf::Color::Blue)
             {
               for (int j = 0; j < ghostNo; j++)
               {
                   w_ghost[j]->timer_ghost.restart();
                   w_ghost[j]->isFizzy = true;
                   //w_ghost[j]->die();
               }
                 fruit[i]->shape.setFillColor(sf::Color::Black);
                 (*score)+=25;
             }
         }
         //KOLOROWANIE PUNKTOW NA NOWO
        if (*lives == 0)
        {
            for (int i = 0; i < fruit.size(); i++)
            {
                fruit[i]->shape.setFillColor(sf::Color::Blue);
            }
        }
    }
}

//Przycisniety przycisk
void changeIsPressed(sf::RenderWindow& window, sf::Sprite sprite, bool* isPressed, bool stay)
{
    float x = sf::Mouse::getPosition(window).x;
    float y = sf::Mouse::getPosition(window).y;
    sf::FloatRect mouse = { x, y, 1.f, 1.f };
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sprite.getGlobalBounds().intersects(mouse)) { *isPressed = true; }
    else
    {
        if (stay == true) { *isPressed = true; }
        else *isPressed = false;
    }
}

//MENU - OBSLUGA PRZYCISKÓW
void cr_menu(sf::RenderWindow& window, bool* decision, sf::Sprite sprite, bool* isPressed)
{
    changeIsPressed(window, sprite, isPressed, false);
    if (*isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        *decision = !(*decision);
        std::chrono::milliseconds dura(175);                        //zatrzymanie w celu unikniecia podwojnego klikniecia
        std::this_thread::sleep_for(dura);
    }
}

//WPISZ NICK
void type_nick(sf::Event& event, sf::RenderWindow& window, sf::Sprite sprite, std::string& display, bool* isPressed, bool* isMenu)
{
    if (*isMenu == true) { changeIsPressed(window, sprite, isPressed, true); }
    if (*isPressed && event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode != 8)
        {
            display += static_cast<char> (event.text.unicode);
        }
        else if (event.text.unicode == 8 && display.size() > 0) { display.pop_back(); }
        system("cls");
    }
}

void try_catch() {}

void file_op(bool toOpen, std::string& display, int& bestscore, std::vector<Ranking*>& ranking)
{
    std::fstream plik;
    if (toOpen)
    {
        plik.open("assets/data/ranking.txt", std::ios::in);
        int i = 0;
        while (!plik.eof())
        {
            ranking.push_back(new Ranking());
            plik >> ranking[i]->wynik;
            std::getline(plik, ranking[i]->nick);
            i += 1;
        }
        //for (int i = 0; i < ranking.size(); i++)
        //{
        //    std::cout << ranking[i]->wynik << " | " << ranking[i]->nick << std::endl;
        //}
        plik.close();
    }

    if (!toOpen)
    {
        plik.open("assets/data/ranking.txt", std::ios::out | std::ios::trunc);
        if (display != "")
        {
            for (int i = 0; i < ranking.size(); i++)
            {
                if (*(ranking[i]) <= bestscore)
                {
                    ranking.insert(ranking.begin() + i, new Ranking);
                    ranking[i]->wynik = bestscore;
                    ranking[i]->nick = display;
                    break;
                }
            }

        }
        for (int i = 0; i < ranking.size(); i++)
        {
            plik << ranking[i]->wynik << " " << ranking[i]->nick << "\n";
        }
        plik.close();
    }
}