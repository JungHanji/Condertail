#pragma once
#include <AdtClasses/AdtClasses.hpp>
#include <MathLib/Vector2.hpp>
#include <MathLib/Vector3.hpp>

enum TEXT_POSITIONS{MIDLE, LEFT, RIGHT, MIDLEUP, MIDLEFIXED};

template<class TString>
int maxStringSize(vector<TString> &st){
    int i=0;for(TString &el : st){
        if(el.size()>i){
            i=el.size();
        }
    }
    return i;
}

template<class CC>
void safeput(vector<vector<CC>> &cmap, vec2 pos, CC simb){
    if(pos > vec2(-1, -1) && pos < vec2(cmap[0].size(), cmap.size())){
        cmap[(int)(pos.y)][(int)(pos.x)] = simb;
    }
}

void placeTextInToMap(vector<vector<wstring>> &rgmap, vector<wstring> text, TEXT_POSITIONS ttpos, vec2 pos, vec3 charcolor, vec3 bgcolor, TEXT_POSITIONS posText = LEFT, vec2 res = {150, 35}){
    int maxStSize = maxStringSize(text);

    switch(posText){
        case MIDLE:{
            pos = {(int)res.x/2 - (int)maxStSize/2, (int)res.y/2 - (int)text.size()/2};
            break;
        }
        case MIDLEUP:{
            pos = {(int)res.x/2 - (int)maxStSize/2, pos.y};
            break;
        }
        case RIGHT:{
            pos = {res.x - pos.x - maxStSize, pos.y};
            break;
        }
    }
    
    switch (ttpos){
        case MIDLE:{
            for(int y = pos.y; y < pos.y + (int)text.size(); y++){
                for(int x = pos.x; x < min((int)pos.x + (int)text[y-(int)pos.y].size(), (int)rgmap[0].size()); x++){
                    if((int)text[y-(int)pos.y].size()!=maxStSize){
                        safeput(rgmap, {x + (maxStSize / 2 - (int)text[y-(int)pos.y].size()/2), y}, wrgbBGString(bgcolor, wrgbFRChar(charcolor, text[y-(int)(pos.y)][x-(int)pos.x])));
                    } else {
                        safeput(rgmap, {x, y}, wrgbBGString(bgcolor, wrgbFRChar(charcolor, text[y-(int)(pos.y)][x-(int)pos.x])));
                    }
                }
            }
            break;
        }

        case LEFT:{
            for(int y = pos.y; y < pos.y + (int)text.size(); y++){
                for(int x = pos.x; x < min((int)pos.x + (int)text[y-(int)pos.y].size(), (int)rgmap[0].size()); x++){
                    safeput(rgmap, {x, y}, wrgbBGString(bgcolor, wrgbFRChar(charcolor, text[y-(int)(pos.y)][x-(int)pos.x])));
                }
            }
            break;
        }

        case RIGHT:{
            for(int y = pos.y; y < pos.y + (int)text.size(); y++){
                for(int x = pos.x; x < min((int)pos.x + (int)text[y-(int)pos.y].size(), (int)rgmap[0].size()); x++){
                    if((int)text[y-(int)pos.y].size()!=maxStSize){
                        safeput(rgmap, {x + (maxStSize - (int)text[y-(int)pos.y].size()), y}, wrgbBGString(bgcolor, wrgbFRChar(charcolor, text[y-(int)(pos.y)][x-(int)pos.x])));
                    } else {
                        safeput(rgmap, {x, y}, wrgbBGString(bgcolor, wrgbFRChar(charcolor, text[y-(int)(pos.y)][x-(int)pos.x])));
                    }
                }
            }
            break;
        }
    }
}

void placeTextInToMapClear(vector<vector<wstring>> &rgmap, vector<wstring> text, TEXT_POSITIONS ttpos, vec2 pos, TEXT_POSITIONS posText = LEFT, vec2 res = {150, 35}){
    int maxStSize = maxStringSize(text);

    switch(posText){
        case MIDLE:{
            pos = {(int)pos.x + (int)res.x/2 - (int)maxStSize/2, (int)pos.y + (int)res.y/2 - (int)text.size()/2};
            break;
        }
        case MIDLEUP:{
            pos = {(int)res.x/2 - (int)maxStSize/2, pos.y};
            break;
        }
        case RIGHT:{
            pos = {res.x - pos.x - maxStSize, pos.y};
            break;
        }
        case MIDLEFIXED:{
            pos = {(int)pos.x + (int)maxStSize/2, (int)pos.y + (int)res.y/2};
        }
    }
    
    switch (ttpos){
        case MIDLE:{
            for(int y = pos.y; y < pos.y + (int)text.size(); y++){
                for(int x = pos.x; x < min((int)pos.x + (int)text[y-(int)pos.y].size(), (int)rgmap[0].size()); x++){
                    if((int)text[y-(int)pos.y].size()!=maxStSize){
                        safeput(rgmap, {x + (maxStSize / 2 - (int)text[y-(int)pos.y].size()/2), y}, to_wstring(text[y-(int)(pos.y)][x-(int)pos.x]));
                    } else {
                        safeput(rgmap, {x, y}, to_wstring(text[y-(int)(pos.y)][x-(int)pos.x]));
                    }
                }
            }
            break;
        }

        case LEFT:{
            for(int y = pos.y; y < pos.y + (int)text.size(); y++){
                for(int x = pos.x; x < min((int)pos.x + (int)text[y-(int)pos.y].size(), (int)rgmap[0].size()); x++){
                    safeput(rgmap, {x, y}, to_wstring(text[y-(int)(pos.y)][x-(int)pos.x]));
                }
            }
            break;
        }

        case RIGHT:{
            for(int y = pos.y; y < pos.y + (int)text.size(); y++){
                for(int x = pos.x; x < min((int)pos.x + (int)text[y-(int)pos.y].size(), (int)rgmap[0].size()); x++){
                    if((int)text[y-(int)pos.y].size()!=maxStSize){
                        safeput(rgmap, {x + (maxStSize - (int)text[y-(int)pos.y].size()), y}, to_wstring(text[y-(int)(pos.y)][x-(int)pos.x]));
                    } else {
                        safeput(rgmap, {x, y}, to_wstring(text[y-(int)(pos.y)][x-(int)pos.x]));
                    }
                }
            }
            break;
        }
    }
}

void clearMap(vector<vector<wstring>> &rmap, wstring bg = wpixel({0, 0, 0})){
    int strsize = rmap[0].size();
    for(vector<wstring> &layer : rmap){
        for(wstring &str : layer){
            str = bg;
        }
    }
}

void insertImage(vec2 pos, Image img, vector<vector<wstring>> &rgmap, vec3 alphaColor = {255, 255, 255}){
    vec3 a;
    for(int y = 0; y < img.height; y++){
        for(int x = 0; x < img.width; x++){
            a = img.getPixelOnImage({x,y});
            if(a!=alphaColor){safeput(rgmap, {pos.x + x, pos.y+y}, wpixel(a));}//rgmap[pos.y+y][pos.x+x] = wpixel(a);}
        }
    }
}