//
// Created by max on 07.06.19.
//

#ifndef GAME_MATTER_H
#define GAME_MATTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

const double     Poison_for_Square  = 10.0;
const double    Poison_for_Mass     = 1000.0;
const double    Poison_for_coord    = -1;
const double    Poison_for_speed    = 0;
const double    Poison_for_accel    = 0;
const double    Poison_for_mobil    = -42;
const size_t    Poison_for_time     = 0xffffffffffffffff;
const int       Poison_for_Health   = -18;
const double    Kryptonite          = 0;

const double double_pres = 0.0001;

const double viscos = 0.01;
const double envir  = 0.1;
const double meat   = 10;
const double proportion = 1;

class Matter {
private:

    double x;
    double y;
    double v_x;
    double v_y;
    double a_x;
    double a_y;
    double F_x;
    double F_y;

    double m;
    double S_x;
    double S_y;

    double B; // mobility

    int Is_seen;
    int Is_alive;

public:

    size_t  d_t;
    int     Hp;
    int     num_sprite;
    sf::Texture mytexture;

    Matter();
    Matter(double coor_x, double coor_y, double mass, int Health, double square_x, double square_y, double force_x, double force_y, sf::Texture &text);
    Matter(const Matter& Copy, double coor_x, double coor_y);
    ~Matter();

    void    Calc_param();
    void    Calc_accel();
    double  Calc_angle();
    void    Set_force(double force_x, double force_y);

    virtual void draw(sf::RenderTarget* screen);
};


#endif //GAME_MATTER_H
