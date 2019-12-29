//
// Created by max on 10.06.19.
//

#ifndef GAME_EAT_H
#define GAME_EAT_H

#include "Matter.h"


class Eat : public Matter
{
private:
    int type;
public:

    Eat(double coor_x, double coor_y, double mass, int Health, double square_x, double square_y, double force_x, double force_y, int type_food, sf::Texture &havka);
    //~Eat();

    //void draw(sf::RenderTarget* screen) override;
};


#endif //GAME_EAT_H
