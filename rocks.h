#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <ctime>
#include "TextureManager.hpp"
#include "Rocket.hpp"

#ifndef FINAL_ROCKS_H
#define FINAL_ROCKS_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

void generaterock();
class Rocket;
class smallrock;
class sun;

class rockbase
{
public:
    ~rockbase();
    void move();
    virtual void operator++() = 0;
    virtual bool test(Rocket a,int) = 0;
    static int rocknum;
protected:
    int x, y;
    int width;
    int height;
    int dx, dy;
    uint32_t seed;
};
class bigrock:public rockbase
{
    friend class Rocket;
    friend class smallrock;
    const int width;
    const int height;
public:
    bigrock(int, int);
    bigrock(int,int,int,int);
    void operator++();
    bool test(Rocket a, int);
private:
    void operator+(bigrock &a);
};
class smallrock:public rockbase
{
    friend class bigrock;
    friend class Rocket;
public:
    smallrock(int x, int y);
    smallrock(int x,int y,int dx,int dy);
    void operator++ ();
    bool test(Rocket a,int);
private:
    void checkCollision(bigrock &a);
    void checkCollision(smallrock &a);
    const int width;
    const int height;
};
extern std::vector<bigrock> bigrocks;
extern std::vector<smallrock> smallrocks;
extern std::vector<rockbase *> rocks;
#endif