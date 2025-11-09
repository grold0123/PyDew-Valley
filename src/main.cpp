#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"
#include<iostream>
#include<vector>

using namespace std;
using window = SDL_Window*;
using renderer = SDL_Renderer*;
using event = SDL_Event;



int main(){
    bool setup = SDL_Init(SDL_INIT_VIDEO);    
    window w = SDL_CreateWindow("SDL Window",700,500,SDL_WINDOW_RESIZABLE);
    renderer r = SDL_CreateRenderer(w,NULL);

    bool inGame = true;
    event e;
    while (inGame) {
        {            
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_EVENT_QUIT) inGame = false;
            }
        }
        {

        }
        {
            {
                SDL_SetRenderDrawColor(r,0,0,255,255);
                SDL_RenderClear(r);
            }
            SDL_RenderPresent(r);
        }
    }
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();    
}


/*
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\hello.exe
build\hello.exe

g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\sdl_window.exe
build\sdl_window.exe
*/
