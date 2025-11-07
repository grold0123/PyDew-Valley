/**********************************
SDL_window
**********************************/
#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"

const char
*title;

int 
width,
height;

SDL_Window
*window;

SDL_Renderer
*renderer;

SDL_Event 
event;

bool
running;

int main(){
    
    title = "Create a SDL window";
    width = 700;
    height = 520;
    window = nullptr;
    renderer = nullptr;
    running = true;

    if (!SDL_Init(SDL_INIT_VIDEO)) return -1;
    if (!SDL_CreateWindowAndRenderer(title,width,height,SDL_WINDOW_RESIZABLE,&window,&renderer)) return -1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
