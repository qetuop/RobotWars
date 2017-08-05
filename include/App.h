#ifndef __APP_H__
#define __APP_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Event.h"
#include "TextureBank.h"

#include "Player.h"
#include "NPC.h"
#include "Timer.h"
#include "MapUtil.h"


#include <memory>

const int JOYSTICK_DEAD_ZONE = 8000;

static const int SCREEN_WIDTH = 640;//1280; //1024;
static const int SCREEN_HEIGHT = 480;//720;//768;

//const int PLAYER_WIDTH = 80;
//const int PLAYER_HEIGHT = 80;

const int BULLET_RATE = 10; // TODO: this will be modifable

//The frame rate
const int FRAMES_PER_SECOND = 60;



void my_audio_callback(void *userdata, Uint8 *stream, int len);

class App : public Event {
    
private:
    static App Instance;

    bool Running = true;

    SDL_Window* Window = NULL;
    SDL_Renderer* Renderer = NULL;
    //SDL_Surface* PrimarySurface = NULL;
    SDL_Joystick *mJoystick;
    SDL_GameController *mGameController;

    //The frame rate regulator
    Timer fps;



    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000;

    Texture* TestTexture;

    std::shared_ptr<Player> mPlayerPtr;
    //std::shared_ptr<NPC> mNPCPtr;
    
    //The sound effects that will be used
     Mix_Chunk *mPew = NULL;
     
     MapUtil map;

private:
    //    public:
    App();

    // Capture SDL Events
    void OnEvent(SDL_Event* Event);

    // Initialize our SDL game / app
    bool Init();

    // Logic loop
    void Loop();

    // Render loop (draw)
    void Render();

    // Free up resources
    void Cleanup();
    
    //void my_audio_callback(void *userdata, Uint8 *stream, int len);

public:
    int Execute(int argc, char* argv[]);
    SDL_Renderer* GetRenderer();

    static App* GetInstance();

    static int GetWindowWidth();
    static int GetWindowHeight();
    
    std::shared_ptr<NPC> mNPCPtr; // temp?
    
    void shoot();
};

#endif
