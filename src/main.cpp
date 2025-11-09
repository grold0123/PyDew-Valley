#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

enum frame{DOWNIDLE,UPIDLE,LEFTIDLE,RIGHTIDLE,
    DOWN,UP,LEFT,RIGHT};

using animation_frames = unordered_map<frame,vector<SDL_Texture*>> ;

int main(){
    SDL_Window
    *window = nullptr;

    SDL_Renderer 
    *renderer = nullptr;

    const char
    *title = "SDL window";

    int 
    width = 500 , height = 500;

    SDL_WindowFlags 
    windowFlag = SDL_WINDOW_RESIZABLE;

    
    {//sdl setup
        if (!SDL_Init(SDL_INIT_VIDEO)) return false;
        if (!SDL_CreateWindowAndRenderer(
            title,
            width,
            height,
            windowFlag,
            &window,
            &renderer
        ))return false;        
    }
    {//game loop
        
        bool inGame = true; SDL_Event event;

        animation_frames animationFrames;
        
        {//load textures
            animationFrames[DOWNIDLE] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down_idle\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down_idle\1.png)"),
            };
            animationFrames[UPIDLE] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\up_idle\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\up_idle\1.png)"),
            };
            animationFrames[RIGHTIDLE] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\right_idle\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\right_idle\1.png)"),
            };
            animationFrames[LEFTIDLE] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\left_idle\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\left_idle\1.png)"),
            };
            animationFrames[LEFT] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\left\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\left\1.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\left\2.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\left\3.png)"),
            };
            animationFrames[RIGHT] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\right\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\right\1.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\right\2.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\right\3.png)"),
            };
            animationFrames[UP] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\up\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\up\1.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\up\2.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\up\3.png)"),            
            };
            animationFrames[DOWN] = vector<SDL_Texture*>{
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down\0.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down\1.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down\2.png)"),
            IMG_LoadTexture(renderer,R"(C:\projects\PyDew-Valley\assets\graphics\character\down\3.png)"),
            };

        }
        
        frame playerState = DOWNIDLE;
        frame previouseState = playerState;

        double frameIndex = 0;

        SDL_Texture *player = animationFrames[playerState][frameIndex];
        SDL_FRect rect = {0,0,0,0};
        SDL_GetTextureSize(player,&rect.w,&rect.h);

        double 
        currentTime = 0.0 , lastTime = 0.0 , deltaTime = 0.0;

        bool keypress = true;

        while (inGame) {
            {//pollevent
                while (SDL_PollEvent(&event)) {                    
                    if (event.type == SDL_EVENT_QUIT) inGame = false;                    
                    else if (event.type == SDL_EVENT_KEY_DOWN) keypress = true;
                    else if (event.type == SDL_EVENT_KEY_UP) keypress = false;
                }                
            }
            {//update
                {//keypress
                    const bool *keystate = SDL_GetKeyboardState(nullptr);
                    if (keypress){
                        if (keystate[SDL_SCANCODE_W]) playerState = UP;
                        else if (keystate[SDL_SCANCODE_S]) playerState = DOWN;
                        else if (keystate[SDL_SCANCODE_A]) playerState = LEFT;
                        else if (keystate[SDL_SCANCODE_D]) playerState = RIGHT;
                                                
                    }
                    else {
                        switch (playerState) {
                            case UP : playerState = UPIDLE ; break;
                            case DOWN : playerState = DOWNIDLE ; break;
                            case RIGHT : playerState = RIGHTIDLE ; break;
                            case LEFT : playerState = LEFTIDLE ; break;
                            default : break;
                        }
                    }                    
                }
                {//delta time
                    currentTime = static_cast<double>(SDL_GetTicks());
                    deltaTime = (currentTime - lastTime) / 1000.0;
                    lastTime = currentTime;
                }
                {//increase frame index
                    {//reset if change in state
                        if (previouseState != playerState) frameIndex = 0.0;
                    }
                    frameIndex += 7.5 * deltaTime;                    
                    {//reset index
                        if (frameIndex >= (animationFrames[playerState]).size()) frameIndex = 0.0;
                    }                    
                }
                {//index texture with state and frame index
                    player = animationFrames[playerState][static_cast<int>(frameIndex)];
                    previouseState = playerState;
                }
            }
            {//render
                {//renderer clear 
                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
                    SDL_RenderClear(renderer);
                }
                {
                    SDL_RenderTexture(renderer,player,nullptr,&rect);
                }
                SDL_RenderPresent(renderer);
            }
        }        
    }

    {//sdl cleanup
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
}

/*
hello world
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\hello.exe

sdl window
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\sdl_window.exe

load texture
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\load_texture.exe

change frame mechanic
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\change_frame.exe

change player states and index from there
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\player_state_indexing.exe
*/