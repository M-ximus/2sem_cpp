//
// Created by max on 10.06.19.
//

#include "Eat.h"

Eat::Eat(double coor_x, double coor_y, double mass, int Health, double square_x, double square_y, double force_x,
         double force_y, int type_food,sf::Texture &havka):
         Matter(coor_x, coor_y, mass, Health, square_x, square_y, force_x, force_y, havka),
         type(type_food)
{
    num_sprite = type_food;
}