#pragma once
#include "init.hpp"

class Player{
    public:

    vec2 pos;
    bool async = true, canMove = true;
    map<string, Image> animImgs;
    string animName = "static_forw";
    int niw = 0,nis = 0,nia = 0,nid = 0;
    float speed = 2;

    Player(vec2 pos): pos(pos){
        animImgs["walk_right"] = Image(homeSprites+"/Frisk/walk_right.bmp");
        animImgs["walk_left"] = Image(homeSprites+"/Frisk/walk_left.bmp");
        animImgs["walk_forw"] = Image(homeSprites+"/Frisk/walk_forw.bmp");
        animImgs["walk_back"] = Image(homeSprites+"/Frisk/walk_back.bmp");
        animImgs["static_right"] = Image(homeSprites+"/Frisk/static_right.bmp");
        animImgs["static_left"] = Image(homeSprites+"/Frisk/static_left.bmp");
        animImgs["static_forw"] = Image(homeSprites+"/Frisk/static_forw.bmp");
        animImgs["static_back"] = Image(homeSprites+"/Frisk/static_back.bmp");
    }
    Player(){;}

    void update(bool canUp, bool canDown, bool canLeft, bool canRight){
        if(async && canMove){
            if(hidhandler.isKeyPressed('w') && canUp){
                pos -= vec2(0, speed);
                if(niw == 3){animName = "static_back";niw = 0;}else{animName = "walk_back";}
                niw ++;
            } else if(hidhandler.isKeyPressed('s') && canDown){
                pos += vec2(0, speed);
                if(nis == 3){animName = "static_forw";nis = 0;}else{animName = "walk_forw";}
                nis ++;
            } else if(hidhandler.isKeyPressed('a') && canLeft){
                pos -= vec2(speed*2, 0);
                if(nia == 3){animName = "static_left";nia = 0;}else{animName = "walk_left";}
                nia ++;
            } else if(hidhandler.isKeyPressed('d') && canRight){
                pos += vec2(speed*2, 0);
                if(nid == 3){animName = "static_right";nid = 0;}else{animName = "walk_right";}
                nid ++;
            }
        } else if(canMove) {
            char gch = (char)getch();
            if(gch == 'w' && canUp){
                pos -= vec2(0, speed);
            } else if(gch == 's' && canDown){
                pos += vec2(0, speed);
            }

            if(gch == 'a' && canLeft){
                pos -= vec2(speed*2, 0);
            } else if(gch == 'd' && canRight){
                pos += vec2(speed*2, 0);
            }
        }
    }

    Image getCurrImg(){
        return animImgs[animName];
    }

    template<class game>
    void onCollision(vec3 color, vector<vector<wstring>> &rgmap, game *gpointer, vec2 scpos){
        ;
    }
};