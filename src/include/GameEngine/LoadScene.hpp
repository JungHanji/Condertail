#pragma once
#include "init.hpp"
#include "Scenes.hpp"

Scenes LoadScene(string pathToSettings){
    vector<string> fileLines = getFileLines(pathToSettings);
    Scenes outScene("Flowey-1");
    vector<pair<vec2, string>> poses;
    
}