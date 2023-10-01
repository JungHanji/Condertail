#pragma once

#include <ConEN/Engine.hpp>

HIDHandler hidhandler;
string homeSprites = "res/Sprites";
wchar_t plSimb = L'♥';
vec2 res = {150, 50};

#include <conio.h>
#include "rgmapTools.hpp"


class plidHandler{
    public:

    bool econtinue(){return hidhandler.isKeyPressed('z') || hidhandler.isKeyPressed(VK_RETURN);}
    bool cancell(){return hidhandler.isKeyPressed('x') || hidhandler.isKeyPressed(VK_SHIFT);}
    bool menu(){return hidhandler.isKeyPressed('c') || hidhandler.isKeyPressed(VK_CONTROL);}
    bool fullscreen(){return hidhandler.isKeyPressed(VK_F4);}
    bool isUp(){return hidhandler.isKeyPressed(VK_UP);}
    bool isDown(){return hidhandler.isKeyPressed(VK_DOWN);}
    bool isLeft(){return hidhandler.isKeyPressed(VK_LEFT);}
    bool isRight(){return hidhandler.isKeyPressed(VK_RIGHT);}
    bool exit(){return hidhandler.isKeyPressed(VK_ESCAPE);}

    plidHandler(){;}
} pidhandler;

void init(){
    soundplayer.saveMusic("startMenu", "res/Sounds/Start_Menu_music.wav", true);
    soundplayer.saveMusic("Mus_flowey", "res/Sounds/Mus_flowey.wav", true);
}