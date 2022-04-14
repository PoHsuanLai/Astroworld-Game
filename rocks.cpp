#include "Rocket.hpp"
#include "rocks.h"
#include <iostream>
using namespace std;

extern TextureManager *rocktext, *smallrocktext;
static smallrock small(rand() % 1066, rand() * 700);


void bigrock::operator++()
{
    rocktext->render(x, y);
}
void smallrock::operator++()
{
    smallrocktext->render(x, y);
}
rockbase::~rockbase() {}
//void bigrock::checkCollision(bigrock &a)
//{
//    int leftx, rightx, topy, buty;
//    bool collide = false;
//    leftx = a.x;
//    rightx = a.x+a.width;
//    topy = a.y;
//    buty = a.y+a.height;
//    if(abs(rightx-x-100)<=50 && abs(leftx-x)<=50 && abs(topy - y)<=50 && abs(buty-y-100) <= 50)   collide = true;
//    if(collide) {
//        if(this->dx!=a.dx)
//        {
//            cout<<"test1"<<endl;
//            swap(a.dx,this->dx);
//            a.dx*=-1;
//            this->dx*=-1;
//        }
//        if(this->dy!=a.dy)
//        {
//            cout<<"test2"<<endl;
//            swap(a.dy,this->dy);
//            a.dy*=-1;
//            this->dy*=-1;
//        }
//    }
//}
void smallrock::checkCollision(bigrock &a)
{
    int leftx, rightx, topy, buty;
    bool collide = false;
    leftx = a.x;
    rightx = a.x+a.width;
    topy = a.y;
    buty = a.y+a.height;
    if(x+width == leftx && y>=topy && y<=buty) collide = true;
    if(x == rightx && y >= topy && y <= buty) collide = true;
    if(y == buty && x >= leftx && x <= rightx) collide = true;
    if(y == topy && x >= leftx && x <= rightx) collide = true;
    if(collide) {
        int dxp = a.dx;
        int dyp = a.dy;
        a.dx = 2*dx;
        a.dy = 2*dy;
        dx = 2*dxp;
        dy = 2*dyp;
    }
}
void smallrock::checkCollision(smallrock &a)
{
    int leftx, rightx, topy, buty;
    bool collide = false;
    leftx = a.x;
    rightx = a.x+a.width;
    topy = a.y;
    buty = a.y+a.height;
    if(x+width == leftx && y>=topy && y<=buty) collide = true;
    if(x == rightx && y >= topy && y <= buty) collide = true;
    if(y == buty && x >= leftx && x <= rightx) collide = true;
    if(y == topy && x >= leftx && x <= rightx) collide = true;
    if(collide) {
        int dxp = a.dx;
        int dyp = a.dy;
        a.dx = dx;
        a.dy = dy;
        dx = dxp;
        dy = dyp;
    }
}
void generaterock(){
    bigrock* big = new bigrock(rand()%1066, rand()%700);
    for (int i = 0; i < 3; i++) {
        bigrocks.push_back(*big);
        delete big;
        big = new bigrock(rand()%1066, rand()%700);}
    rocks.resize(bigrocks.size()+smallrocks.size());
    for (int i = 0; i < bigrocks.size() ; i++) {
        rocks[i] = &bigrocks[i];
    }
    rocks[0]->rocknum = rocks.size();}
bigrock::bigrock(int x, int y):width(200),height(200)
{
    this->x = x;
    this->y = y;
    dx = rand()%3;
    dy = rand()%2;
    rocktext->LoadTexture("../boss.png");
}
bigrock::bigrock(int x, int y,int dx,int dy):width(200),height(200)
{
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    rocktext->LoadTexture("../boss.png");
}
smallrock::smallrock(int x, int y):width(50),height(50)
{
    seed = (unsigned)time(nullptr);
    srand(seed);
    this->x = x;
    this->y = y;
    dx = rand()%5;
    dy = rand()%3;
    smallrocktext->LoadTexture("../boss1.png");
}
smallrock::smallrock(int x, int y,int dx,int dy):width(50),height(50)
{
    seed = (unsigned)time(nullptr);
    srand(seed);
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    smallrocktext->LoadTexture("../boss1.png");
}
void rockbase::move()
{

    double newX = x+dx;
    double newY = y+dy;

    int colX = 0, colY = 0;

    int right = (newX + width - 1) >= SCREEN_WIDTH -1,
            left = newX < 0-1,
            top = (newY - height + 1) < 0+1,
            bottom = newY >= SCREEN_HEIGHT -1;
    if(right){
        colX = 1;
    }
    if(left){
        colX = 1;
    }
    if(top){
        colY = 1;
    }
    if(bottom){
        colY = 1;
    }

    if(!colX){
        x = newX;
    }
    else{
        dx *= -1;
    }
    if(!colY){
        y = newY;
    }
    else{
        dy *= -1;
    }
    if(!dx && !dy) {
        dx += rand()%6;
        dy += rand()%4;
    }
}
bool smallrock::test(Rocket a, int i)
{
    int rightx, leftx, topy, buty;
    rightx = a.x + a.ROCKET_WIDTH/2.0;
    leftx = a.x - a.ROCKET_WIDTH/2.0;
    topy = a.y -a.ROCKET_HEIGHT/2.0;
    buty = a.y + a.ROCKET_HEIGHT/2.0;

    //cout<<a.x<<" "<<a.y<<" "<<x<<" "<<y<<endl;
    bool collide = false;
    if(rightx>=x && leftx<=x+width && topy >= y && buty <= y + height)   collide = true;
    if(collide) {
        smallrocks.erase(smallrocks.begin()+i-bigrocks.size());
        rocks.erase(rocks.begin()+i-bigrocks.size());
    }
    smallrocks[0].rocknum -= 1;
    return true;
}


bool bigrock::test(Rocket a, int i)
{
    int rightx, leftx, topy, buty;
    rightx = a.x + a.ROCKET_WIDTH/2.0;
    leftx = a.x - a.ROCKET_WIDTH/2.0;
    topy = a.y -a.ROCKET_HEIGHT/2.0;
    buty = a.y + a.ROCKET_HEIGHT/2.0;
    bool collide = false;1
    if(rightx>=x && leftx<=x+width && topy >= y && buty <= y + height)   collide = true;
    if(!collide)    return false;
    if (collide) {
        int N = rocks.size();
        int big_x = bigrocks[i].x,big_y = bigrocks[i].y;

        bigrocks.erase(bigrocks.begin()+i);
        rocks.erase(rocks.begin()+i);

        srand(time(NULL));
        int xx[3],yy[3];
        xx[0] = rand()%10;
        srand(1);
        xx[1] = rand()%10;
        srand(2);
        xx[2] = rand()%10;
        yy[0] = rand()%10;
        yy[1] = rand()%10;
        yy[2] = rand()%10;

        for (int j = 0; j < 3; j++)
        {
            smallrock * newsmall =  new smallrock(big_x, big_y,xx[j],yy[j]);
            smallrocks.push_back(*newsmall);
            rocks.push_back(newsmall);
        }
    }
    bigrocks[i].rocknum += 2;
    return collide;
}

void bigrock::operator+(bigrock &a)
{
    int leftx, rightx, topy, buty;
    bool collide = false;
    leftx = a.x;
    rightx = a.x+a.width;
    topy = a.y;
    buty = a.y+a.height;
    if(x+width == leftx) collide = true;
    if(x == rightx) collide = true;
    if(y == buty) collide = true;
    if(y+height == topy) collide = true;
    if(collide) {
        int dxp = a.dx;
        int dyp = a.dy;
        a.dx = dx;
        a.dy = dy;
        dx = dxp;
        dy = dyp;

    }
    return;
}












