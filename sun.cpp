#include "sun.h"
#include <cmath>

extern TextureManager suntext;
sun::sun(double x0, double y0){
    x = x0; y = y0;
}

//template <typename u>
void sun::push(Rocket &a)
{
    double dist = sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y));
    a.dx -= ((0.3/dist*dist)*((a.x-x)/dist))/2;
    a.dy -= ((0.3/dist*dist)*((a.y-y)/dist))/2;
}

void sun::render(){
    suntext.render(x, y);
}

bool sun::checkCollision(double x0, double y0){
    if(abs(x-x0)<60&&abs(y-y0)<60) return true;
    else return false;
}
