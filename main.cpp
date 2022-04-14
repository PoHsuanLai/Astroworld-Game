#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>
#include <vector>
#include <cstdio>
#include <string>
#include "TextureManager.cpp"
#include "Rocket.cpp"
#include "PowerUps.cpp"
#include "sun.h"
#include "particles.h"
#include "rocks.h"
using namespace std;

//const int SCREEN_WIDTH = 1066;
//const int SCREEN_HEIGHT = 800;

//function declare
bool init();
bool loadMedia();
void close();
void render();
void updateBoost(Rocket &rocket, Rocket &rocket2, int &rocket_cooldown, int &rocket2_cooldown);
bool win(Rocket &rocket, Rocket &rocket2, sun &sun);
void restart(Rocket& rocket, Rocket& rocket2);

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *surface1 = nullptr, *surface2 = nullptr, *surface3 = nullptr, *textsurface = nullptr, *replaysurface = nullptr, *returnsurface = nullptr;
SDL_Texture *texture1 = nullptr, *texture2 = nullptr, *texture3 = nullptr, *texttexture = nullptr, *replaytexture = nullptr, *returntexture = nullptr;
Mix_Music *mymusic;
TextureManager *rocktext = new TextureManager, *smallrocktext = new TextureManager;
TTF_Font *gFont = NULL;
SDL_Rect fontrect= {230, 70, 600, 200}, replayrect = {560, 500, 400, 200}, returnrect = {150, 500, 250, 200 };
TextureManager *RocketTexture = new TextureManager[16];
TextureManager suntext;
TextureManager PowerUpsTexture[5];
LTexture gRedTexture;

vector<rockbase *> rocks;
vector<bigrock> bigrocks;
vector<smallrock> smallrocks;

//function define
bool init(){

    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        window = SDL_CreateWindow( "AstroG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                int mflags = MIX_INIT_MP3;
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                if(TTF_Init() == -1){
                    printf("cannot load ttf");
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(){
    bool success = true;
    mymusic = Mix_LoadMUS("../song2.mp3");
    if(mymusic == nullptr){
        printf("failed to load music!\n");
        success = false;
    }

    if(!RocketTexture[0].LoadTexture("../P1_90.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[1].LoadTexture("../P1_22.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[2].LoadTexture("../P1_45.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }if(!RocketTexture[3].LoadTexture("../P1_67.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[4].LoadTexture("../P1_0.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[5].LoadTexture("../P1_292.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[6].LoadTexture("../P1_315.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[7].LoadTexture("../P1_337.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[8].LoadTexture("../P1_270.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[9].LoadTexture("../P1_202.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[10].LoadTexture("../P1_225.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[11].LoadTexture("../P1_247.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[12].LoadTexture("../P1_180.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[13].LoadTexture("../P1_112.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[14].LoadTexture("../P1_135.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!RocketTexture[15].LoadTexture("../P1_157.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!PowerUpsTexture[0].LoadTexture("../Reverse.png")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!PowerUpsTexture[1].LoadTexture("../Speed.png")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!PowerUpsTexture[2].LoadTexture("../Blades.png")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!PowerUpsTexture[3].LoadTexture("../Laser.png")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!PowerUpsTexture[4].LoadTexture("../Mine.png")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!suntext.LoadTexture("../sun.png")){
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if(!gRedTexture.loadFromFile("../red.bmp")){
        printf("Failed to load dot texture!\n");
        success = false;
    }

    gFont = TTF_OpenFont( "../myfont.ttf", 30);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    return success;
}

void page3(Rocket& rocket, Rocket& rocket2){
    SDL_Color color = {255, 255, 255, 255};
    if(rocket2.death == 3)textsurface = TTF_RenderText_Solid( gFont, "Player Left Wins!", color );
    else if (rocket.death == 3)textsurface = TTF_RenderText_Solid( gFont, "Player Right Wins!", color );
    replaysurface = TTF_RenderText_Solid(gFont, "Play again", color);
    replaytexture = SDL_CreateTextureFromSurface(renderer, replaysurface);
    returnsurface = TTF_RenderText_Solid(gFont, "Menu", color);
    returntexture = SDL_CreateTextureFromSurface(renderer, returnsurface);
    texttexture = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_RenderCopy(renderer, replaytexture, nullptr, &replayrect);
    SDL_RenderCopy(renderer, texttexture, nullptr, &fontrect);
    SDL_RenderCopy(renderer, returntexture, nullptr, &returnrect);
}

void close(){
    for(int i=0;i<16;i++){
        RocketTexture[i].free();
    }
    for(int i=0; i<5; i++){
        PowerUpsTexture[i].free();
    }
    suntext.free();
    gRedTexture.free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    Mix_FreeMusic(mymusic);
    mymusic = nullptr;

    IMG_Quit();
    SDL_Quit();
}



int main(int argc, char *args[])
{

    int page = 1;
    unsigned int lastTime = 0, currentTime;
    srand((unsigned)time(NULL));

    if(!init()){
        printf("Failed to initialize!\n");
    }
    else{
        if(!loadMedia()){
            printf("Failed to load media!\n");
        }
        else{
            surface1 = IMG_Load("../Menu.jpeg");
            texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
            surface2 = IMG_Load("../space.bmp");
            texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
            surface3 = IMG_Load("../over.jpeg");
            texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
            bool quit = false;

            SDL_Event e;
            SDL_Event e2;

            Rocket rocket(0, 0, 0);
            Rocket rocket2(180, SCREEN_WIDTH-70, SCREEN_HEIGHT-70);
            int PU_cooldown = 0;
            PowerUps PUArray[5] = {
                    PowerUps(0, rand()%1066, rand() %700),
                    PowerUps(1, rand()%1066, rand() %700),
                    PowerUps(2, rand()%1066, rand() %700),
                    PowerUps(3, rand()%1066, rand() %700),
                    PowerUps(4, rand()%1066, rand() %700)
            };
            int rocket_cooldown = 0;
            int rocket2_cooldown = 0;
            restart(rocket, rocket2);

            sun sun(SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2-50);
            bigrock big(rand()%1066, rand()%700);
            smallrock small(rand() % 1066, rand() % 700);
            generaterock();

            const int FPS = 60;
            const int frameDelay = 1000/FPS;
            uint32_t frameStart;
            int frameTime;
            while(!quit){

                if (Mix_PlayingMusic() == 0) {
                    //Play the music
                    Mix_PlayMusic(mymusic, -1);
                }
                while(SDL_PollEvent(&e)!=0||SDL_PollEvent(&e2)!=0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    if(page==2){
                        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                            //Adjust the velocity
                            switch( e.key.keysym.sym ){
                                case SDLK_e: rocket.ang_vel+=rocket.ang_accle; break;
                                case SDLK_w: rocket.boostRocket(); break;
                                case SDLK_q: rocket.ang_vel = 0; break;
                                case SDLK_p: rocket2.ang_vel+=rocket2.ang_accle; break;
                                case SDLK_o: rocket2.boostRocket();  break;
                                case SDLK_i: rocket2.ang_vel = 0; break;
                            }
                        }
                        if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
                            //Adjust the velocity
                            switch( e.key.keysym.sym ){
                                case SDLK_e: rocket.ang_vel-=rocket.ang_accle; break;
                                case SDLK_p: rocket2.ang_vel-=rocket2.ang_accle; break;

                            }
                        }

                    }
                }
                currentTime = SDL_GetTicks();
                if (currentTime > lastTime + 1000) {
                    lastTime = currentTime;
                }

                //menu
                if(page==1){
                    SDL_SetTextureBlendMode(texture1, SDL_BLENDMODE_BLEND);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture1, nullptr, nullptr);
                    SDL_RenderPresent(renderer);
                }
                else if(page==2){
                    frameStart = SDL_GetTicks();
                    //handle event
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture2, nullptr, 0);
                    //handle event end
                    //update
                    rocket.rotateRocket();
                    rocket2.rotateRocket();
                    rocket.accelerateRocket();
                    rocket.moveRocket();
                    rocket2.accelerateRocket();
                    rocket2.moveRocket();
                    sun.push(rocket);
                    sun.push(rocket2);
                    int N = rocks.size();
                    if((currentTime/1000)%7 == 6 && currentTime%1000<=10) generaterock();
                    for (int i = 0; i < rocks.size() ; i++) {
                        if(rocks[i] == nullptr ) continue;
                        rocks[i]->move();
                        rocks[i]++;
                        if(rocks[i]->test(rocket, i) ) {
                            i--;
                        }
                    }
                    for (int i = 0; i < rocks.size() ; i++) {
                        if (rocks[i] == nullptr) continue;
                        //rocks[i]->move();
                        rocks[i]++;
                        if (rocks[i]->test(rocket2, i)) {
                            i--;
                        }
                    }

                    for(int i=0; i<5; i++){
                        if(PU_cooldown%1600==0) PUArray[rand()%2].show = true;
                        PU_cooldown++;
                        if(PUArray[i].show&&abs(PUArray[i].x-533)>50&&abs(PUArray[i].y-350)>50){
                            PUArray[i].render();
                            PUArray[i].checkPU(rocket, rocket2);
                        }
                        else{
                            PUArray[i].x = rand()%1026+20;
                            PUArray[i].y = rand()%660+20;
                        }
                    }
                    //update end
                    //render
                    rocket.render();
                    rocket2.render();
                    rocket.renderParticles();
                    rocket2.renderParticles();
                    sun.render();

                    //boost & powerups
                    updateBoost(rocket, rocket2, rocket_cooldown, rocket2_cooldown);
                    rocket.UpdatePowerUps();
                    rocket2.UpdatePowerUps();


                    if(win(rocket, rocket2, sun)){
                        page = 4;
                    }

                    SDL_RenderPresent(renderer);
                    if(rocket.death == 3 || rocket2.death == 3){
                        SDL_Delay(1000);
                        page = 3;
                    }
                    //render end
                    frameTime = SDL_GetTicks() - frameStart;
                    if(frameDelay>frameTime){
                        SDL_Delay(frameDelay - frameTime);
                    }
                }
                else if (page == 3){
                    SDL_SetTextureBlendMode(texture3, SDL_BLENDMODE_BLEND);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture3, nullptr, nullptr);
                    page3(rocket, rocket2);
                    SDL_RenderPresent(renderer);
                }
                else if(page == 4){
                    rocket.reset(0, 0, 0);
                    rocket2.reset(180, SCREEN_WIDTH-70, SCREEN_HEIGHT-70);
                    for(int i=0;i<5;i++){
                        PUArray[i].show = false;
                    }
                    SDL_Color color = {255, 255, 255, 255};
                    if(rocket2.death == 2)
                        returnsurface = TTF_RenderText_Solid(gFont, "Left Point: 2", color);
                    else if(rocket2.death == 1)
                        returnsurface = TTF_RenderText_Solid(gFont, "Left Point: 1", color);
                    else if(rocket2.death == 0)
                        returnsurface = TTF_RenderText_Solid(gFont, "Left Point: 0", color);
                    else if(rocket2.death == 3)
                        returnsurface = TTF_RenderText_Solid(gFont, "Left Point: 3", color);
                    if(rocket.death == 2)
                        replaysurface = TTF_RenderText_Solid(gFont, "Right Point 2", color);
                    else if(rocket.death == 1)
                        replaysurface = TTF_RenderText_Solid(gFont, "Right Point: 1", color);
                    else if(rocket.death == 0)
                        replaysurface = TTF_RenderText_Solid(gFont, "Right Point: 0", color);
                    else if(rocket.death == 3)
                        replaysurface = TTF_RenderText_Solid(gFont, "Right Point: 3", color);

                    replaytexture = SDL_CreateTextureFromSurface(renderer, replaysurface);
                    returntexture = SDL_CreateTextureFromSurface(renderer, returnsurface);

                    SDL_RenderCopy(renderer, replaytexture, nullptr, &replayrect);
                    SDL_RenderCopy(renderer, returntexture, nullptr, &returnrect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    page = 2;
                }
                int mousex, mousey;
                SDL_GetMouseState(& mousex, &mousey);
                if (e.button.clicks == 1 && mousex <= 1486 * 1066 / 2224 && mousex >= 730 * 1066 / 2224 &&
                    mousey >= 1160 * 800 / 1668 && mousey <= 1307 * 800 / 1668 && page == 1) {
                    page = 2;
                    restart(rocket, rocket2);
                }
                if(e.button.clicks == 1 && mousex <= 960 && mousex >= 560 &&
                   mousey >= 500 && mousey <= 700 && page == 3){
                    page = 2;
                    restart(rocket, rocket2);
                }
                if(e.button.clicks == 1 && mousex <= 400 && mousex >= 150 &&
                   mousey >= 500 && mousey <= 700 && page == 3) {
                    page = 1;
                    Mix_CloseAudio();
                    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
                    Mix_PlayMusic(mymusic, -1);
                }
            }
        }
    }
    close();
    return 0;
}

void updateBoost(Rocket &rocket, Rocket &rocket2, int &rocket_cooldown, int &rocket2_cooldown){

    if(rocket.rocketBoost!=3){
        rocket_cooldown++;
        if(rocket_cooldown==rocket.boost_cooldown){
            rocket.rocketBoost++;
            rocket_cooldown = 0;
        }
    }
    if(rocket2.rocketBoost!=3){
        rocket2_cooldown++;
        if(rocket2_cooldown==rocket2.boost_cooldown){
            rocket2.rocketBoost++;
            rocket2_cooldown = 0;
        }
    }
}


bool win(Rocket &rocket, Rocket &rocket2, sun &sun){
    if(sun.checkCollision(rocket.x, rocket.y)){
        rocket--; return true;
    }
    else if(sun.checkCollision(rocket2.x, rocket2.y)){
        rocket2--; return true;
    }
    else if(rocket.checkwin(rocket2)){
        rocket2--; return true;
    }
    else if(rocket2.checkwin(rocket)){
        rocket--; return true;
    }
    else return false;
}

void restart(Rocket& rocket, Rocket& rocket2){
    rocket.reset(0,0,0);
    rocket2.reset(180,SCREEN_WIDTH-70, SCREEN_HEIGHT-70);
    rocket.death = 0;
    rocket2.death = 0;
}


