#pragma once
#include "init.hpp"
#include "Dialogs.hpp"

class NPC{
    public:
    vec2 pos;
    string name;
    vector<Image> imgs;
    Image mainImg, dlg_sc, dlg_tk;
    vector<vector<wstring>> replics;
    using CallbackType = std::function<void(NPC*, int)>;
    
    vector<pair<int, CallbackType>> fevents;
    bool moving = false, nearWithPlayer = false, dialogActive = false, startedActions = false;
    int distnce, tick = 0, replInd = 0;

    NPC(string name, string scenary_file, string pathToImg, string pathToImg_dlg, string pathToImg_tlk, vec2 stPos, int distnce, bool cmove = false){
        this->name = name;
        this->distnce = distnce;
        mainImg.load(pathToImg);
        dlg_sc.load(pathToImg_dlg);
        dlg_tk.load(pathToImg_tlk);
        pos = stPos;
        moving = cmove;

        vector<wstring> fl_lines = getFileLinesW(scenary_file);
        
        //bool addDialog = false;
        //for(wstring &line : fl_lines){
        //    if(line == L"::Dialog"){addDialog = true;} 
        //    else {addDialog = false;}
        //}
        /*
        terminate called after throwing an instance of 'std::bad_array_new_length'
        what():  std::bad_array_new_length
        */
        //cout<<2<<endl;
        //vector<vector<wstring>> t = splitVec(fl_lines, to_wstring(L'-'));
        //vector<wstring> el;
        //cout<<4<<endl;
        //el.push_back(L"::Battle_wind\n");
        //cout<<index<vector<wstring>>(t, el)<<endl;
        //vector<vector<wstring>> replics = sliceVec(t, 0, index<vector<wstring>>(t, el, true));
        //cout<<1<<endl;
        //for(auto &el : replics){
        //    writeToFileW("x", el, 'a');
        //}
    }

    void move(vec2 force){
        ;
    }

    void Dialog(vector<vector<wstring>> &rgmap, Player &player){
        if(dialogActive){
            player.canMove = false;
            //while(replInd != replics.size()-1){
            makeRect(rgmap, {3, 1}, {rgmap[0].size() - 6, 10});
            insertImage({5,3}, dlg_sc ,rgmap, {0, 0, 0});
            placeTextInToMap(rgmap, replics[replInd], LEFT, {3 + dlg_sc.width + 5, 3}, {255, 255, 255}, {0, 0, 0});
            if(pidhandler.econtinue()){
                replInd++;
            }
            if(replInd==replics.size()){
                player.canMove = true;
                tick = 0;
                dialogActive = false;
            }
            //}
            tick++;
        }
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

    void addPhrase(vector<wstring> repl){
        replics.push_back(repl);
    }

    template<class TSC>
    void update(vector<vector<wstring>> &rgmap, TSC *scene, Player &player){
        scene->insertImage(pos, mainImg);
        nearWithPlayer = ((pos - (vec2(distnce, (int)(distnce/2)) + vec2(6, 5))) < player.pos) && (player.pos < (pos + vec2(mainImg.width, mainImg.height) + vec2(distnce, (int)(distnce/2))));
        if(nearWithPlayer && !dialogActive && !startedActions){startedActions = true;dialogActive = true;}
        if(dialogActive){
            Dialog(rgmap, player);
        }
        rgmap.back().back() = to_wstring(nearWithPlayer);
    }

    NPC(){}
};


void floweyFirstLockIntro(NPC &flowey){
    soundplayer.playMusic("Mus_flowey");
}