#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#ifndef Texture_H_
#define Texture_H_

class TextureManager{
public:
    TextureManager();
    ~TextureManager();

    bool LoadTexture(std::string path);

    #if defined(_SDL_TTF_H) || defined(SDL_TTF_H_)
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif

    //Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, \
                    double angle = 0.0, SDL_Point* center = NULL, \
                    SDL_RendererFlip flip = SDL_FLIP_NONE ) const;

    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;

    int width;
    int height;
};

#endif
