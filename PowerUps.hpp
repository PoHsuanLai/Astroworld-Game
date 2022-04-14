#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <iostream>

#ifndef POWERUPS_H
#define POWERUPS_H

class Rocket;
class PowerUps{
public:
    enum powerups {Reverse, Speed, Grow, Bomb };
    bool show;
    int id;
    int x, y;
    PowerUps();
    PowerUps(int i, int x0, int y0);
    void render();
    void checkPU(Rocket&, Rocket&);
};

#endif // POWERUPS_H
