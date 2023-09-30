#pragma once
#include "init.hpp"
#include "Dialogs.hpp"

class NPC{
    public:
    vec2 pos;
    string name;
    vector<Image> imgs;
    Image mainImg, dlg_sc, dlg_tk;
    map<string, Dialog> dialogs;
    vector<string> replics;
    vector<pair<int, function<void(NPC&, int)>>> events;
    bool moving = false, nearWithPlayer = false;
    int distnce, tick = 0;

    NPC(string name, string scenary_file, string pathToImg, string pathToImg_dlg, string pathToImg_tlk, vec2 stPos, int distnce, bool cmove = false){
        this->name = name;
        this->distnce = distnce;
        mainImg.load(pathToImg);
        dlg_sc.load(pathToImg_dlg);
        dlg_tk.load(pathToImg_tlk);
        pos = stPos;
        moving = cmove;
    }

    void move(vec2 force){
        ;
    }

    void startDialog(vector<vector<wstring>> &rgmap, Player &player){
        player.canMove = false;
        makeRect(rgmap, {3, 1}, {rgmap[0].size() - 6, 10});
        insertImage({5,3}, dlg_sc ,rgmap, {0, 0, 0});
        tick++;
    }

    void startBattle(){
        ;
    }

    void startAnimation(){
        ;
    }

    void updateAnims(){
        ;
    }

    template<class TSC>
    void update(vector<vector<wstring>> &rgmap, TSC *scene, Player &player){
        scene->insertImage(pos, mainImg);
        nearWithPlayer = ((pos - (vec2(distnce, (int)(distnce/2)) + vec2(6, 5))) < player.pos) && (player.pos < (pos + vec2(mainImg.width, mainImg.height) + vec2(distnce, (int)(distnce/2))));
        if(nearWithPlayer){startDialog(rgmap, player);}
        rgmap.back().back() = to_wstring(nearWithPlayer);
    }

    NPC(){}
};


void floweyFirstLockIntro(NPC &flowey){
    soundplayer.playMusic("Mus_flowey");
}