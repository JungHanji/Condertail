#include <MathLib/Vector2.hpp>
#include <MathLib/Vector3.hpp>
#include <MathLib/AddMath.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <windows.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool IS_CTRLC_PRESSED = false;

void SetWindow(int Width, int Height){
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

class Image{
    public:

    unsigned char *img;
    int width, height, cnt;
    vec2 aspect = vec2(1);

    Image(std::string fileName){
        img = stbi_load(fileName.c_str(), &width, &height, &cnt, 3);
    }

    void calcAspect(vec2 res){
        aspect = res / vec2(width, height);
    }

    vec3 getPixelOnImage(vec2 pos, vec2 dopAsp = vec2(1, 1)){
        pos *= aspect * dopAsp;
        float r = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 0];
        float g = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 1];
        float b = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 2];
        return {r, g, b};
    }

    vec3 getPixelClear(vec2 pos){
        float r = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 0];
        float g = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 1];
        float b = img[(int)pos.y * width * 3 + (int)pos.x * 3 + 2];
        return {r, g, b};
    }

    void load(string path){
        img = stbi_load(path.c_str(), &width, &height, &cnt, 3);
    }

    Image(){}
};

class SoundPlayer{
    public:
    map<string, pair<bool, string>> sounds;

    void saveMusic(string name, string path, bool looping = false){
        sounds[name] = {looping, path};
    }

    void saveAndPlay(string name, string path){
        saveMusic(name, path);
        playMusic(name);
    }

    void playMusic(string name){
        PlaySound(sounds[name].second.c_str(), NULL, (!sounds[name].first) ? SND_ASYNC : SND_ASYNC | SND_LOOP);
    }

    void justPlay(string path){
        PlaySound(path.c_str(), NULL, SND_ASYNC);
    }

    void stopMusic(){
        PlaySound(NULL, NULL, 0);
    }

    SoundPlayer(){}
} soundplayer;

class HIDHandler{
    public:
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphaStart = 65; 
    int numStart = 48;

    POINT mpoint;

    /*
    a-z and 0-9
    */
    bool isKeyPressed(char key){
        int code = -1;
        if(isdigit(key)){
            code = key - '0';
        } else {
            code = alphaStart + alphabet.find(key);
        }

        if(code!=-1){
            return GetAsyncKeyState(code)  == -32767;
        } else {
            return false;
        }
    }

    bool isKeyPressed(int code){
        return GetAsyncKeyState(code)  == -32767;
    }
    
    /*
    ind 0 = VK_LBUTTON
    ind 1 = VK_RBUTTON
    */
    bool isButtonPressed(int ind){
        return ind == 0 ? (GetAsyncKeyState(VK_LBUTTON) == -32767) : (GetAsyncKeyState(VK_RBUTTON) == -32767);
    }

    vec2 getMousePos(){
        GetCursorPos(&mpoint);
        return {mpoint.x, mpoint.y};
    }

    void setMousePos(vec2 pos){
        SetCursorPos((int)pos.x, (int)pos.y);
    }

    HIDHandler(){}
};

class Screen{
    public:

    HANDLE buffer1, buffer2;
    DWORD buffWritten1, buffWritten2;
    int ActiveBuffer = 0;
    LPDWORD trash;
    Screen(){
        buffer1 = GetStdHandle(STD_OUTPUT_HANDLE);
        buffer2 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    }

    void Write(std::wstring &s){
        WriteConsoleW(ActiveBuffer == 0 ? buffer1 : buffer2,
                      s.c_str(),
                      s.size(),
                      ActiveBuffer == 0 ? &buffWritten1 : &buffWritten2,
                      NULL);
        
    }

    void ShowBuffer(){
        SetConsoleCursorPosition(ActiveBuffer == 0 ? buffer1 : buffer2, {0, 0});
    }

    void SwapBuffers(){
        SetConsoleActiveScreenBuffer(ActiveBuffer == 0 ? buffer1 : buffer2);
        ActiveBuffer == 0 ? ActiveBuffer = 1 : ActiveBuffer = 0;
    }

    void quit(){
        CloseHandle(buffer1);
        CloseHandle(buffer2);
    }
};

void ctrlcHandler(int trash){
    IS_CTRLC_PRESSED = true;
}

class App{
    public:
    vec2 resolution;
    vector<vector<wstring>> gmap;
    wstring bgChar = L" ";

    bool runing = true;
    Screen screen;

    App(vec2 res, wstring bgChar_ = L" "){
        //SetWindow(150,40);
        bgChar = bgChar_;
        resolution = res;
        for(int y = 0; y < res.y; y++){
            gmap.push_back(vector<wstring>());
            for(int x = 0; x < res.x; x++){
                gmap[gmap.size()-1].push_back(bgChar);
            }
        }
    }

    template<class game>
    void run(game agent){
        while(runing){
            char buf[BUFSIZ];
            if ( signal(SIGINT, ctrlcHandler) == SIG_ERR ){
                terminate();
            }
            if(IS_CTRLC_PRESSED) {runing = false;break;}

            
            
            for(int y = 0; y < resolution.y; y++){
                for(int x = 0; x < resolution.x; x++){
                    gmap[y][x] = bgChar;
                }
            }

            wstring appendToFrame = agent.update(gmap, resolution);
            screen.ShowBuffer();

            wstring frame;
            
            for(int y = 0; y < resolution.y; y++){
                for(int x = 0; x < resolution.x; x++){
                    frame+=gmap[y][x];
                }
                frame+='\n';
            }

            if(appendToFrame != L"None") frame += L"\n" + appendToFrame;

            screen.Write(frame);
            screen.SwapBuffers();
        }
        print("END -----------");
        soundplayer.stopMusic();
    }

    App(){}
};