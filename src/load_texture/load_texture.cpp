/**********************************
load_texture
**********************************/
#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"
#include<iostream>
#include<vector>
#include<filesystem>
using namespace std;

const char
*title;

int 
width,
height;

float 
offset_w,
offset_h;

bool
running;

SDL_Window
*window;

SDL_Renderer
*renderer;

SDL_Event 
event;

SDL_Texture 
*player;

vector<SDL_Texture*> 
playerDown,
playerUp,
playerLeft,
playerRight;

SDL_FRect 
playerRect,
playerBox,
playerBox_2;




int main(){
    
    title = "Create a SDL window";
    width = 700;
    height = 520;
    window = nullptr;
    renderer = nullptr;
    running = true;
    
    if (!SDL_Init(SDL_INIT_VIDEO)) return -1;
    if (!SDL_CreateWindowAndRenderer(title,width,height,SDL_WINDOW_RESIZABLE,&window,&renderer)) return -1;

    for (const auto&entry:filesystem::directory_iterator(R"(C:\projects\PyDew-Valley\assets\graphics\character\down)")){
        SDL_Texture*texture = IMG_LoadTexture(renderer,entry.path().string().c_str());
        playerDown.push_back(texture);
    }
    for (const auto&entry:filesystem::directory_iterator(R"(C:\projects\PyDew-Valley\assets\graphics\character\left)")){
        SDL_Texture*texture = IMG_LoadTexture(renderer,entry.path().string().c_str());
        playerLeft.push_back(texture);
    }
    for (const auto&entry:filesystem::directory_iterator(R"(C:\projects\PyDew-Valley\assets\graphics\character\right)")){
        SDL_Texture*texture = IMG_LoadTexture(renderer,entry.path().string().c_str());
        playerRight.push_back(texture);
    }
    for (const auto&entry:filesystem::directory_iterator(R"(C:\projects\PyDew-Valley\assets\graphics\character\up)")){
        SDL_Texture*texture = IMG_LoadTexture(renderer,entry.path().string().c_str());
        playerUp.push_back(texture);
    }

    player = IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down\0.png)");
    playerRect.x = playerRect.y = 0;
    SDL_GetTextureSize(player,&playerRect.w,&playerRect.h);

    
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_UP) cout << "Player Position: (" << playerRect.x << "," << playerRect.y << ")\n";
        }
        
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderFillRect(renderer,&playerBox);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&playerBox_2);

         SDL_RenderTexture(renderer,player,NULL,&playerRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

vector2D::vector2D():
    x(0),y(0){}
vector2D::vector2D(float a,float b):
    x(a),y(b){}
