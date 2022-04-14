#include "TextureManager.hpp"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font *gFont;
TextureManager::TextureManager(){
    texture = NULL;
    width = 0;
    height = 0;
}

TextureManager::~TextureManager(){
    free();
}

bool TextureManager::LoadTexture(std::string path){

    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x05, 0xFF, 0x0D ) );
//		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,255, 255, 255));

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == nullptr )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H_)
bool TextureManager::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return texture != NULL;
}
#endif

void TextureManager::free(){
    if(texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void TextureManager::setColor( Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void TextureManager::setBlendMode( SDL_BlendMode blending){
    SDL_SetTextureBlendMode(texture, blending);
}

void TextureManager::setAlpha( Uint8 alpha){
    SDL_SetTextureAlphaMod(texture, alpha);
}

void TextureManager::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center,  SDL_RendererFlip flip) const {
    SDL_Rect renderQuad = { x, y, width, height};
    if(clip!=NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip);
}

int TextureManager::getWidth(){
    return width;
}

int TextureManager::getHeight(){
    return height;
}
