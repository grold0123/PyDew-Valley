/**********************************
animate_frames
**********************************/
#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"
#include<iostream>
#include<vector>
#include<filesystem>
using namespace std;

enum 
playerDirection {UP,DOWN,RIGHT,LEFT,IDLE};

const char
*title;

const bool
*keystate;

struct vector2D{
    vector2D();
    vector2D(float a, float b);
    float x,y;
};

int 
width,
height;

float 
offset_w,
offset_h,
playerSpeed,
nowTick,
deltaTime,
friction,
animationSpeed,
playerFrameIndex;

bool
running;

Uint64
lastTick;

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
playerRight,
currentFrames;

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
    
    playerFrameIndex = 0.0f;

    player = playerDown[playerFrameIndex];    
    playerRect.x = playerRect.y = 0;
    SDL_GetTextureSize(player,&playerRect.w,&playerRect.h);

    playerDirection currentDirection = DOWN;    
    playerDirection lastDirection = currentDirection;

    vector2D position{playerRect.x,playerRect.y};
    vector2D acceleration;
    vector2D velocity;
    vector2D direction;
    friction = .3;
    playerSpeed = 1000;
    animationSpeed = 20;
    
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_UP) cout << "Player Position: (" << playerRect.x << "," << playerRect.y << ")\n";
        }
        
        nowTick = SDL_GetTicks();
        deltaTime = static_cast<float>(nowTick - lastTick)/1000.0f;
        lastTick = nowTick;

        direction = {0,0};

        keystate = SDL_GetKeyboardState(nullptr);

        if (keystate[SDL_SCANCODE_W]) {
            direction.y = -1;
            currentDirection = UP;
        }
        else if (keystate[SDL_SCANCODE_S]) {
            direction.y = 1;
            currentDirection = DOWN;
        }

        if (keystate[SDL_SCANCODE_A]) {
            direction.x = -1;
            currentDirection = LEFT;
        } 
        else if (keystate[SDL_SCANCODE_D]) {
            direction.x = 1;
            currentDirection = RIGHT;
        } 

        acceleration.x = direction.x * playerSpeed;
        acceleration.y = direction.y * playerSpeed;

        velocity.x += acceleration.x * deltaTime;
        velocity.y += acceleration.y * deltaTime;

        if (direction.x == 0 && direction.y == 0) {
            velocity.x *= friction;
            velocity.y *= friction;
        }

        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        playerRect.x = position.x;
        playerRect.y = position.y;

        if (lastDirection == DOWN) currentFrames = playerDown;
        else if (lastDirection == UP) currentFrames = playerUp;
        else if (lastDirection == RIGHT) currentFrames = playerRight;
        else if (lastDirection == LEFT) currentFrames = playerLeft;                        

        if (currentDirection != lastDirection) playerFrameIndex = 0;

        if (!(direction.x == 0 && direction.y == 0)) {
            playerFrameIndex += animationSpeed * deltaTime;                        
            lastDirection = currentDirection;
            cout << "Frame Addition: " << animationSpeed * deltaTime << endl;
            cout << "Frame count: " << playerFrameIndex << endl;
            if (playerFrameIndex >= currentFrames.size()) playerFrameIndex = 0;
            player = currentFrames[static_cast<int>(playerFrameIndex)];
        }
        else player = currentFrames[0];
        
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
