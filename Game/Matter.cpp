//
// Created by max on 07.06.19.
//

#include <cassert>
#include "Matter.h"

Matter::Matter() :
    x(0),
    y(0),
    v_x(0),
    v_y(0),
    a_x(0),
    a_y(0),
    F_x(0),
    F_y(0),
    m(Poison_for_Mass),
    S_x(Poison_for_Square),
    S_y(Poison_for_Square),
    B(0),

    d_t(0),

    Is_alive(0),
    Is_seen(0),

    Hp(0),
    num_sprite(-1)
{}

Matter::Matter(double coor_x, double coor_y, double mass, int Health, double square_x, double square_y, double force_x, double force_y, sf::Texture &text)
{
    assert(coor_x >= 0);
    assert(coor_y >= 0);
    assert(mass >= 0);
    assert(square_x >= 0);
    assert(square_y >= 0);

    assert(std::isfinite(force_x));
    assert(std::isfinite(force_y));

    x = coor_x;
    y = coor_y;
    m = mass;
    S_x = square_x;
    S_y = square_y;
    F_x = force_x;
    F_y = force_y;
    Hp  = Health;

    B = envir * S_x;

    v_x = 0;
    v_y = 0;
    a_x = 0;
    a_y = 0;

    d_t = 0;

    Is_alive = 1;
    Is_seen = 0;

    num_sprite = -1;

    mytexture = text;//TODO check operator for malloc
}

Matter::Matter(const Matter& Copy, double coor_x, double coor_y)
{
    assert (coor_x >= 0);
    assert (coor_y >= 0);

    x = coor_x;
    y = coor_y;

    v_x = 0;
    v_y = 0;
    a_x = 0;
    a_y = 0;

    F_x = Copy.F_x;
    F_y = Copy.F_y;

    m = Copy.m;
    S_x = Copy.S_x;
    S_y = Copy.S_y;

    B = envir * S_x;

    d_t = 0;

    Is_alive = 1;
    Is_seen = 0;

    Hp = (int) (m * meat);

    num_sprite =Copy.num_sprite;

    mytexture = Copy.mytexture;
}

Matter::~Matter()
{
    x = Poison_for_coord;// assert with killed object
    y = Poison_for_coord;

    v_x = Poison_for_speed;
    v_y = Poison_for_speed;

    a_x = Poison_for_accel;
    a_y = Poison_for_accel;

    F_x = Kryptonite;
    F_y = Kryptonite;

    m = Poison_for_Mass;

    S_x = Poison_for_Square;
    S_y =  Poison_for_Square;

    B = Poison_for_mobil;

    d_t = Poison_for_time;

    Is_seen = -1;
    Is_alive = -1;

    Hp = Poison_for_Health;

    num_sprite = -1;
}

void Matter::Calc_param()
{
    if (Is_alive !=  1)
        return;

    x += (v_x * d_t) + (a_x * d_t * d_t / 2);
    y += (v_y * d_t) + (a_y * d_t * d_t / 2);

    v_x += a_x * d_t;
    v_y += a_y * d_t;
}

void Matter::Calc_accel()
{
    if (Is_alive != 1)
        return;

    double Stocks = v_x * B;
    a_x = (F_x + Stocks) / m;

    Stocks = v_y * B;
    a_y = (F_y + Stocks) / m;
}

double Matter::Calc_angle()
{
    if (Is_alive != 1)
        return NAN;

    double angle = 0;

    if (v_x <= (-double_pres) || v_x >= (double_pres))
    {
        angle = atan(v_y / v_x);
        if (v_y < 0)
            angle += M_PI;
    }
    else if (v_y >= 0)
        angle = M_PI_2;
    else
        angle = M_PI_2 + M_PI;

    return angle;
}

void Matter::Set_force(double force_x, double force_y)
{
    assert(std::isfinite(force_x));
    assert(std::isfinite(force_y));

    F_x = force_x;
    F_y = force_y;
}

void Matter::draw(sf::RenderTarget* screen)
{
    assert(screen != nullptr);
    if (Is_alive != 1 || num_sprite < 0)//TODO is seen
        return;

    sf::CircleShape shape(100.f);
    //screen->draw(shape);

    float scale = (float) (m * proportion);
    sf::Sprite sprite;
    sprite.setTextureRect(sf::IntRect (num_sprite * ((int) S_x), 0, (num_sprite + 1) * ((int) S_x), (int) S_y));
    //sprite.setOrigin((float)(S_x / 2), (float)(S_y / 2));

    printf("%p", sprite.getTexture());

    //sprite.rotate((float)Calc_angle());
    //sprite.setScale(scale, scale);
    sprite.setPosition((float) x, (float) y);

    screen->draw(sprite);
}
