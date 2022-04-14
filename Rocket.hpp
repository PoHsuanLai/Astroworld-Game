#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <iostream>
#include "particles.h"

#ifndef ROCKET_H_
#define ROCKET_H_
#include "rocks.h"
#include "PowerUps.hpp"

class sun;
//const int TOTAL_PARTICLES = 20;
class Rocket{
    friend class bigrock;
    friend class smallrock;
    friend class sun;
public:

    Rocket(double ang, double x, double y);
    //~Rocket();

    void handleEvent(SDL_Event& e, int id);
    void moveRocket();
    void rotateRocket();
    void accelerateRocket();
    void boostRocket();
    bool checkwin(Rocket &enemy);
    void reset(double ang, int x0, int y0);
    void UpdatePowerUps();
    void render();
    Rocket operator--(int);

    static const int ROCKET_WIDTH = 75;
    static const int ROCKET_HEIGHT = 75;
    double x, y, dx, dy;
    int rocketBoost = 3;
    const int boost_cooldown = 100;
    int death;

    bool PU_reverse;
    bool PU_speed;
    bool PU_blade;
    bool PU_laser;
    bool PU_mine;
    void renderParticles();
    int ang_vel = 10;
    const int ang_accle = 2;

private:
    int angle;
    int color;
    int dir;
    int accel = 6;
    int ROCKET_V = 12;

    int shotCooldown;
    int PUS_cooldown;


    const int boost_speed = 50;
    const int hitbox = 30;
    const double dt = 0.033333;
    Particle *particles[20];
};


#endif

