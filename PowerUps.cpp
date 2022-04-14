#include "TextureManager.hpp"
#include "PowerUps.hpp"
#include "Rocket.hpp"

extern TextureManager PowerUpsTexture[5];

PowerUps::PowerUps(int i, int x0, int y0){
    id = i;
    x = x0, y = y0;
    show = false;
}

void PowerUps::render(){
    PowerUpsTexture[id].render(x, y);
}

void PowerUps::checkPU(Rocket &rocket, Rocket &rocket2){
    if(abs(rocket.x-x)<75&&abs(rocket.y-y)<75){
        switch(id){
            case 0: rocket.PU_reverse = (rocket.PU_reverse ? false : true);
                    rocket2.PU_reverse = (rocket2.PU_reverse ? false : true); show = false;
            case 1: rocket.PU_speed = true; show = false;
            case 2: rocket.PU_blade = true; show = false;
            case 3: rocket.PU_laser = true; show = false;
            case 4: rocket.PU_mine = true; show = false;
        }
    }
    if(abs(rocket2.x-x)<75&&abs(rocket2.y-y)<75){
        switch(id){
            case 0: rocket.PU_reverse = (rocket.PU_reverse ? false : true);
                    rocket2.PU_reverse = (rocket2.PU_reverse ? false : true); show = false;
            case 1: rocket2.PU_speed = true; show = false;
            case 2: rocket2.PU_blade = true; show = false;
            case 3: rocket2.PU_laser = true; show = false;
            case 4: rocket2.PU_mine = true; show = false;
        }
    }
}
