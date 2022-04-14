#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <iostream>
#include "TextureManager.hpp"
#include "rocks.h"
#include "Rocket.hpp"

#ifndef FINAL_SUN_H
#define FINAL_SUN_H

#endif //FINAL_SUN_H

class sun
{
private:
    double x, y;
public:
    sun(double x0, double y0);
    void render();
    void push(Rocket&);
    bool checkCollision(double x0, double y0);
};
