#include "TextureManager.hpp"
#include "Rocket.hpp"


#define PI 3.14159265359
#define PI8 PI/8


//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* window;

//The window renderer
extern SDL_Renderer* renderer;

//Scene textures
extern TextureManager *RocketTexture;

Rocket::Rocket(double ang, double x0, double y0)
{
    //Initialize the offsets
    x = x0;
    y = y0;
    dx = 0;
    dy = 0;
    angle = ang;
    dir = angle/22.5;
    rocketBoost = 3;
    death = 0;
    PU_reverse = false;
    PU_speed = false;
    PU_blade = false;
    PU_laser = false;
    PU_mine = false;
    PUS_cooldown = 0;
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[ i ] = new Particle( x, y );
    }
}


void Rocket::handleEvent( SDL_Event& e , int id)
{
    //If a key was pressed
	if(e.type == SDL_KEYDOWN)
    {
        //rotate and shoot
        if(id == 1){
            switch( e.key.keysym.sym )
            {
                case SDLK_e: rotateRocket(); break;
                case SDLK_q: boostRocket(); break;
            }
        }
        else if(id == 2){
            switch( e.key.keysym.sym )
            {
                case SDLK_p: rotateRocket(); break;
                case SDLK_i: boostRocket(); break;
            }
        }
    }
}

void Rocket::rotateRocket(){
    if(!PU_reverse){
        if(angle == 0){
            angle = 360 - ang_vel;
        }
        else{
            angle = (angle - ang_vel) % 360;

        }
    }
    else{
        angle = (angle + ang_vel) % 360;
    }
    dir = angle/22.5;
}

void Rocket::accelerateRocket(){
    double theta = PI8 * dir;
    double t_x = cos(theta) * ROCKET_V;
    double t_y = -sin(theta) * ROCKET_V;

    if(fabs(dx-t_x)<dt*accel){
        dx = t_x;
    }
    else if(dx<t_x){
        dx += dt*accel;
    }
    else if(dx>t_x){
        dx -= dt*accel;
    }

    if(fabs(dy-t_y)<dt*accel){
        dy = t_y;
    }
    else if(dy<t_y){
        dy += dt*accel;
    }
    else if(dy>t_y){
        dy -= dt*accel;
    }
}

void Rocket::moveRocket()
{
    //Move the dot left or right
    double newX = x+dx;
    double newY = y+dy;

    int colX = 0, colY = 0;

    bool right = (newX + ROCKET_WIDTH/2 ) >= SCREEN_WIDTH,
        left = newX < 0,
        top = (newY + 50 - ROCKET_HEIGHT/2) < 0,
        bottom = newY + 50 >= SCREEN_HEIGHT;
    int sum = right + left + top + bottom + colX + colY;

    if(sum == 2){
        return;
    }
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
        dx = 0;
    }
    if(!colY){
        y = newY;
    }
    else{
        dy = 0;
    }
}

void Rocket::boostRocket(){
    if(rocketBoost>0){
        double theta = PI8 * dir;
        double bdx = cos(theta) * boost_speed;
        double bdy = -sin(theta) * boost_speed;
        double newX = x+bdx;
        double newY = y+bdy;

        if(newX < 0){
            newX = 1;
        }
        if(newY < 0){
            newY = 1;
        }
        if(newX > SCREEN_WIDTH-ROCKET_WIDTH/2){
            newX = SCREEN_WIDTH-ROCKET_WIDTH/2-3;
        }
        if(newY > SCREEN_HEIGHT-ROCKET_HEIGHT/2-30){
            newY = SCREEN_HEIGHT-ROCKET_HEIGHT/2-30;
        }

        dx += bdx/10;
        dy += bdy/10;

        x = newX;
        y = newY;
        rocketBoost --;
    }
}

bool Rocket::checkwin(Rocket &enemy){
    double theta = PI8*dir;
    double pX = x + 28*cos(theta);
    double pY = y - 28*sin(theta);
    bool w = false;
    if(abs(pX-enemy.x)<hitbox&&abs(pY-enemy.y)<hitbox){
        w = true;
    }
    return w;
}

void Rocket::render()
{
    //Show the rocket
    RocketTexture[dir].render(x, y);
}

void Rocket::reset(double ang, int x0, int y0){
    x = x0;
    y = y0;
    dx = 0;
    dy = 0;
    angle = ang;
    ang_vel = 0;
    accel = 3;
    ROCKET_V = 6;
    dir = angle/22.5;
    rocketBoost = 3;
    PU_reverse = false;
    PU_speed = false;
    PU_blade = false;
    PU_laser = false;
    PU_mine = false;
    PUS_cooldown = 0;
}

void Rocket::UpdatePowerUps(){
    if(PU_speed){
        accel = 10;
        ROCKET_V = 15;
        PUS_cooldown++;
        if(PUS_cooldown == 300){
            PU_speed = false;
            accel = 6;
            ROCKET_V = 12;
            PUS_cooldown = 0;
        }
    }
}
Rocket Rocket::operator--(int){
    death++;
}
void Rocket::renderParticles()
{
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        //Delete and replace dead particles
        if( particles[ i ]->isDead() )
        {
            delete particles[ i ];
            particles[ i ] = new Particle( x, y);
        }
    }

    //Show particles
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[ i ]->render();
    }
}