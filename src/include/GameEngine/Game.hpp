#pragma once
#include "init.hpp"
#include "Player.hpp"
#include "Dialogs.hpp"
#include "NPC.hpp"
#include "Scenes.hpp"
#include "Cutscenes.hpp"
#include "Menu.hpp"

class Game{
    public:
    Player player;
    int tick = 0, indMap = 0;
    bool canPlayerUpdate = false, startMenu = true;

    Scenes activeScene;
    Game(){
        player = Player({(int)(150 / 2) - 5, (int)(35 / 2) - 2});
        activeScene.load("Ruins");
    }

    void getNextMap(){
        indMap++;
        if(indMap >= locations.size()){indMap = 0;}
        activeScene.load(locations[indMap].first);
        player.pos = locations[indMap].second;
    }

    wstring update(vector<vector<wstring>> &rgmap, vec2 res){
        wstring msg = L"";
        

        if(startMenu){
            bool canContinue = SttMenu.update(rgmap);
            if(canContinue){startMenu = false; canPlayerUpdate = true;}
        }


        if(canPlayerUpdate){
            
            if(debug && hidhandler.isKeyPressed('n')){getNextMap();}
            for(int y = 0; y < res.y; y++){
                for(int x = 0; x < res.x; x++){
                    if(activeScene.getGrPix({x, y}) != vec3(255, 255, 255))
                        rgmap[y][x] = stringToWstring(pixel(activeScene.getGrPix({x, y})));
                }
            }
            
            vec3 collColor = activeScene.getRealPhPix({player.pos.x, player.pos.y}),
                 gcColor   = activeScene.getRealGrPix({player.pos.x, player.pos.y});

            
            activeScene.update(rgmap, player);
            player.update(player.pos.y - player.speed > 0 && activeScene.canWalk({player.pos.x, player.pos.y-player.speed}), player.pos.y + player.speed < (activeScene.size.y) && activeScene.canWalk({player.pos.x, player.pos.y+player.speed}) && player.pos.y + 5 + player.speed < (activeScene.size.y) && activeScene.canWalk({player.pos.x, player.pos.y + 5 + player.speed}), player.pos.x - player.speed > 0 && activeScene.canWalk({player.pos.x-player.speed, player.pos.y}), player.pos.x + player.speed < (activeScene.size.x) && activeScene.canWalk({player.pos.x+player.speed, player.pos.y}) && player.pos.x + 11 + player.speed < (activeScene.size.x-1) && activeScene.canWalk({player.pos.x + 11 + player.speed, player.pos.y})); // up, down, left, right
            insertImage({(int)(150 / 2), (int)(35 / 2)}, player.getCurrImg(), rgmap);   
            activeScene.move(player.pos - vec2((int)(150 / 2), (int)(35 / 2)));

            
            if(collColor != vec3(255, 255, 255) && collColor != vec3(0, 0, 0)){
                player.onCollision(collColor, rgmap, this, {(int)(150 / 2), (int)(35 / 2)});        
                if(collColor==vec3(0,255,0)){
                    getNextMap();
                }
            }
            
            if(!(player.pos.x > 0 && player.pos.x < activeScene.size.x && player.pos.y > 0 && player.pos.y < activeScene.size.y)){msg += L"Out of the map";}
            
        }


        tick++;
        return L"None";//to_wstring(player.pos.x) + L" " + to_wstring(player.pos.y) + L"\n " + to_wstring(activeScene.size.x) + L" " + to_wstring(activeScene.size.y) + L"\n" + msg + L"\n"+to_wstring(tick);//"None";//
        
    }
};