#pragma once
#include "init.hpp"
#include "NPC.hpp"

bool debug = true;

vector<pair<string, vec2>> locations = {
    {"Ruins", {74, 21}},
    {"Flowey-1", {74, 140}}
};

map<string, pair<function<void(NPC&)>, bool>> collFunctions = {
    {"fl_first_intro", {floweyFirstLockIntro, true}}
};

class Scenes{
    public:
    string name;
    Image gr_map, phis_map;
    vec2 pos = vec2(0, 0), size;
    vector<vector<wstring>> ws_gmap;
    vector<vector<vec3>> px_gmap;

    map<string, pair<NPC, string>> npcs;

    Scenes(string name): name(name){
        gr_map = Image(homeSprites+"/Locations/"+name+"/gr.bmp");
        phis_map = Image(homeSprites+"/Locations/"+name+"/ph.bmp");
        size = vec2(gr_map.width, gr_map.height);
        makeNPCs();
        convertToMMaps();
    }

    void load(string name){
        this->name = name;
        gr_map = Image(homeSprites+"/Locations/"+name+"/gr.bmp");
        phis_map = Image(homeSprites+"/Locations/"+name+"/ph.bmp");
        size = vec2(gr_map.width, gr_map.height);

        makeNPCs();
        convertToMMaps();
    }

    void convertToMMaps(){
        px_gmap.clear();
        for(int y = 0; y < gr_map.height; y++){
            px_gmap.push_back(vector<vec3>());
            ws_gmap.push_back(vector<wstring>());
            for(int x = 0; x < gr_map.width; x++){
                px_gmap[px_gmap.size()-1].push_back(gr_map.getPixelOnImage({x, y}));
                ws_gmap[ws_gmap.size()-1].push_back(wpixel(gr_map.getPixelOnImage({x, y})));
            }
        }
    }

    void makeNPCs(){
        npcs["flowey"] = {
            NPC("flowey", 
                homeSprites+"/Flowey/msc.bmp", homeSprites+"/Flowey/dlg_msc.bmp", homeSprites+"/Flowey/dlg_msc_talking.bmp", 
                {71, 114}, 15),
            "fl_first_intro"
        };
    }

    void insertImage(vec2 pos, Image img, vec3 alphaColor = {255, 255, 255}){
        vec3 a;
        for(int y = 0; y < img.height; y++){
            for(int x = 0; x < img.width; x++){
                a = img.getPixelOnImage({x,y});
                if(a!=alphaColor && (int)pos.y+y >= 0 && (int)pos.y+y < px_gmap.size() && (int)pos.x+x >= 0 && (int)pos.x+x < px_gmap[0].size()){px_gmap[(int)pos.y+y][(int)pos.x+x] = a;}
            }
        }
    }

    void move(vec2 pos){
        this->pos = pos;
    }

    void calcAspect(vec2 res){
        gr_map.calcAspect(res);
        phis_map.calcAspect(res);
    }

    bool canWalk(vec2 pos_){
        if(vec2(0, 0) < (pos_) && (pos_) < size || debug){
            return vec3({0, 0, 0}) != phis_map.getPixelOnImage(pos_);
        } else {
            return false;
        }
    }

    vec3 getGrPix(vec2 pos_){
        if(vec2(-1, -1) < (pos+pos_) && (pos+pos_) < size){
            return px_gmap[(int)(pos.y+pos_.y)][(int)(pos.x+pos_.x)];
        } else {
            return {0, 0, 0};
        }
    }

    vec3 getRealGrPix(vec2 pos_){return gr_map.getPixelOnImage(pos_);};//px_gmap[(int)(pos_.y * gr_map.aspect.y)][(int)(pos_.x * gr_map.aspect.x)];}
    vec3 getRealPhPix(vec2 pos_){return phis_map.getPixelOnImage(pos_);}

    vec3 getPhPix(vec2 pos_){
        if(vec2(-1, -1) < (pos+pos_) && (pos+pos_) < size){
            return phis_map.getPixelOnImage(pos+pos_);
        } else {
            return {0, 0, 0};
        }
    }

    void update(vector<vector<wstring>> &rgmap, Player &player){
        for(auto &el: npcs){
            npcs[el.first].first.update(rgmap, this, player);
            if(npcs[el.first].first.nearWithPlayer && collFunctions[npcs[el.first].second].second){
                collFunctions[npcs[el.first].second].first(npcs[el.first].first);
                collFunctions[npcs[el.first].second].second = false;
            }
        }
    }

    Scenes(){;}
};