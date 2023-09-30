#pragma once
#include "init.hpp"

void makeRect(vector<vector<wstring>> &rgmap, vec2 pos, vec2 size){
    int posx = (int)pos.x, posy = (int)pos.y, sizex = (int)size.x, sizey = (int)size.y;
    for(int y = posy; y < posy + sizey; y++){
        for(int x = posx; x < posx + sizex; x++){
            bool border = (y == posy || y == sizey + posy - 1 || x == posx || x == sizex + posx - 1);
            if(border){
                rgmap[y][x] = wpixel({255, 255, 255});
            } else {
                rgmap[y][x] = wpixel({0, 0, 0});
            }
        }
    }
}

class Dialog{
    public:
    vec2 pos;
    vector<vector<wstring>> texts;
    Image speaker;
    bool pressedCont = true;
    int textInd = 0;
    int typePos = 0;

    Dialog(int typePos, vector<vector<wstring>> texts, string pathToImg){
        this->typePos = typePos;
        this->texts = texts;
        speaker.load(pathToImg);
    }

    void start(){
        ;
    }

    bool update(vector<vector<wstring>> &rgmap){
        ;
    }

    void loadSpeaker(string path){speaker.load(path);}
    void loadSpeaker(Image img){speaker = img;}

    void addPhrase(vector<wstring> phrase){
        texts.push_back(phrase);
    }

    bool isPlayerNearby(int distance){
        ;
    }

    Dialog(){}
};