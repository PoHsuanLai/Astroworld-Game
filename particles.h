#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>

#ifndef FINAL_PARTICLES_H
#define FINAL_PARTICLES_H
const int TOTAL_PARTICLES = 20;

const int SCREEN_WIDTH = 1066;
const int SCREEN_HEIGHT = 800;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

class Rocket;
//The frame rate
class LTexture
{
    friend Rocket;
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path );
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

class Particle
{
public:
    //Initialize position and animation
    Particle( int x, int y );

    //Shows the particle
    void render();

    //Checks if particle is dead
    bool isDead();

    int mFrame;
private:
    //Offsets
    int mPosX, mPosY;

    //Current frame of animation


    //Type of particle
    LTexture *mTexture;
};
extern LTexture gRedTexture;
#endif