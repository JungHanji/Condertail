#pragma once
#include "init.hpp"

/*
Инструкции

z enter - поодтвердить
x shift - отменить
c ctrl - меню
f4 - весь экран
Удерживаете ESC - выйти

Если ОЗ достигент 0, вы проиграете.

Имя упавшего человека
*/

class StartMenu{
    public:

    int screenInd = 0, btnInd = 0;
    bool selectedBtns = false;
    wstring name;
    vec2 pos = {0, 0};

    //vwxyz
    vector<wstring> chars = {
        L"ABCDEFG",
        L"HIJKLMN",
        L"OPQRSTU",
        L"VWXYZ",
        L"abcdefg",
        L"hijklmn",
        L"opqrstu",
        L"vwxyz"
    };

    vector<wstring> charsToShow = {};

    void onStart(vector<vector<wstring>> &rgmap){
        placeTextInToMap(rgmap, {
            L"Инструкции",
            L" ",
            L"[Z  ENTER] - подтвердить",
            L"[X SHIFT] - отменить",
            L"[C CTRL] - меню",
            L"[F4] - весь экран",
            L"[Удерживаете ESC] - выйти",
            L" ",
            L"Если ОЗ достигент 0, вы проиграете."
        }, MIDLE, {0, 0}, {255, 255, 255}, {0, 0, 0}, MIDLE);
    }

    bool update(vector<vector<wstring>> &rgmap){
        vector<wstring> tcharsToShow;
        //soundplayer.stopMusic();return true;//if(debug && hidhandler.isKeyPressed('n')){}
        //a-z; 97 - 122; A - Z 65 - 90
        if(screenInd == 0){
            onStart(rgmap);
            if(pidhandler.econtinue()) {
                screenInd++;
                soundplayer.playMusic("startMenu");
                //clearMap(rgmap);
            }
        } else if(screenInd == 1){
            bool bup = pidhandler.isUp(), bdown = pidhandler.isDown(), br = pidhandler.isRight(), bl = pidhandler.isLeft();

            if(bup && selectedBtns){selectedBtns = false;}
            else if(!selectedBtns && bdown && ((pos.y + 1) >= chars.size())){selectedBtns = true;}

            if(bup && ((pos.y - 1) >= 0) && !selectedBtns){pos.y-=1;} 
            else if(!selectedBtns && bdown && ((pos.y + 1) < chars.size())){pos.y+=1; if(pos.x >= chars[(int)pos.y].size()){pos.x = chars[(int)pos.y].size()-1;}} 
            else if(!selectedBtns && br && ((pos.x + 1) < chars[(int)pos.y].size())){pos.x+=1;} 
            else if(!selectedBtns && bl && ((pos.x - 1) >= 0)){pos.x-=1;}
            else if(selectedBtns && br && btnInd + 1 < 3){btnInd++;}
            else if(selectedBtns && bl && btnInd - 1 >= 0){btnInd--;}
            

            if(!selectedBtns && pidhandler.econtinue()) name += chars[(int)pos.y][(int)pos.x];
            else if(!selectedBtns && hidhandler.isKeyPressed(VK_BACK)) name = slice(name, 0, -1);

            if(selectedBtns && pidhandler.econtinue()){
                switch (btnInd){
                    case 0: exit(2);break;
                    case 1: name = slice(name, 0, -1);break;
                    case 2: screenInd++;btnInd = 1;break;
                }
            }

            for(int y = 0; y < chars.size(); y++){
                tcharsToShow.push_back(L" ");
                for(int x = 0; x < chars[y].size(); x++){
                    if(!selectedBtns) tcharsToShow[tcharsToShow.size()-1] += (vec2(x, y) != pos) ? to_wstring(chars[y][x]) + L"  " : wrgbFRString({255, 255, 0}, to_wstring(chars[y][x]) + L"  ");//wrgbBGString({0, 0, 0}, '');
                    else tcharsToShow[tcharsToShow.size()-1] += to_wstring(chars[y][x]) + L"  ";
                }
            }

            placeTextInToMap(rgmap, {L"Имя упавшего человека."}, LEFT, {0, 5}, {255, 255, 255}, {0, 0, 0}, MIDLEUP);
            placeTextInToMapClear(rgmap, tcharsToShow, LEFT, {65, 15}, LEFT);
            placeTextInToMap(rgmap, {name}, LEFT, {0, 6}, {0, 255, 0}, {0, 0, 0}, MIDLEUP);

            if(selectedBtns){
                placeTextInToMap(rgmap, {L"Выйти"}, LEFT, {65, 26}, ((btnInd != 0)) ? vec3(255, 255, 255) : vec3(255, 255, 0), {0, 0, 0});
                placeTextInToMap(rgmap, {L"Стереть"}, LEFT, {65 + 5 + 1, 26}, ((btnInd != 1)) ? vec3(255, 255, 255) : vec3(255, 255, 0), {0, 0, 0});            
                placeTextInToMap(rgmap, {L"Готово"}, LEFT, {65 + 8 + 5 + 1, 26}, ((btnInd != 2)) ? vec3(255, 255, 255) : vec3(255, 255, 0), {0, 0, 0});
            } else {
                placeTextInToMap(rgmap, {L"Выйти"}, LEFT, {65, 26},vec3(255, 255, 255), {0, 0, 0});
                placeTextInToMap(rgmap, {L"Стереть"}, LEFT, {65 + 5 + 1, 26},vec3(255, 255, 255), {0, 0, 0});            
                placeTextInToMap(rgmap, {L"Готово"}, LEFT, {65 + 8 + 5 + 1, 26},vec3(255, 255, 255), {0, 0, 0});
            }
        } else if(screenInd == 2){
            placeTextInToMap(rgmap, {L"Выбрать это имя?"}, LEFT, {0, 5}, {255, 255, 255}, {0, 0, 0}, MIDLEUP);
            placeTextInToMap(rgmap, {name}, LEFT, {0, 0}, {255, 255, 240}, {0, 0, 0}, MIDLE);
            

            wstring rh = wrgbFRChar({255, 0, 0}, plSimb);
            
            if(pidhandler.isRight()) btnInd = 1;
            else if(pidhandler.isLeft()) btnInd = 0;
            placeTextInToMapClear(rgmap, {(btnInd == 0) ? rh + L"НЕТ" : L"НЕТ"}, LEFT, (btnInd != 0) ? vec2({50, (int)(res.y - res.y/3)}) : vec2({50-1, (int)(res.y - res.y/3)}), LEFT);
            placeTextInToMapClear(rgmap, {(btnInd == 1) ? rh + L"ДА" : L"ДА"}, LEFT, (btnInd != 1) ? vec2({70 + rh.size() * 2, (int)(res.y - res.y/3)}) : vec2({70+rh.size(), (int)(res.y - res.y/3)}), LEFT);
            if(pidhandler.econtinue()){
                switch (btnInd){
                    case 0: screenInd--;break;
                    case 1: screenInd++;soundplayer.stopMusic();break;
                }
            }
        } else if(screenInd == 3){return true;} 
        //placeTextInToMap(rgmap, {to_wstring(screenInd)}, LEFT,{0, 0}, {255, 255, 255}, {0, 0, 0});
        return false; 
    }

    StartMenu(){
        
    }
} SttMenu;

class ShopMenu{
    public:

    vector<pair<int, int>> itemsToSell;

    ShopMenu(){

    }
};

class StatisticMenu{
    public:

    string mp_name;
    int max_hp, max_def, max_atc;
    int lvl, xp, money;

    StatisticMenu(){
        ;
    }
};

class ChestMenu{
    public:

    vector<int> items;

    ChestMenu(){
        ;
    }
};