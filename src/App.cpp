//==============================================================================
#include "App.h"
#include "Log.h"
#include "Event.h"
#include "Helper.h"
#include "Player.h"
#include "Bullet.h"

App App::Instance;

//==============================================================================

App::App( ) {
}

//------------------------------------------------------------------------------

void App::OnEvent( SDL_Event* Event ) {
    Event::OnEvent(Event);
}

//------------------------------------------------------------------------------

bool App::Init( ) {
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        Log("Unable to Init SDL: %s", SDL_GetError());
        return false;
    }

    // set the scaling interpolation algorithm for the whole renderer
    if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }

    // SDL_WINDOW_FULLSCREEN_DESKTOP  |  SDL_WINDOW_SHOWN
    if ( (Window = SDL_CreateWindow(
            "My SDL Game",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)
            ) == NULL ) {
        Log("Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    int display_count = 0;
    int display_index = 0;
    int mode_index = 0;
    SDL_DisplayMode mode = {SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0};

    if ( (display_count = SDL_GetNumVideoDisplays()) < 1 ) {
        SDL_Log("SDL_GetNumVideoDisplays returned: %i", display_count);
        return 1;
    }

    for (; display_index < display_count; display_index++ ) {
        if ( SDL_GetDisplayMode(display_index, mode_index, &mode) != 0 ) {
            SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
            return 1;
        }
        SDL_Log("SDL_GetDisplayMode(0, 0, &mode):\t\t%i bpp\t%i x %i",
                SDL_BITSPERPIXEL(mode.format), mode.w, mode.h);
    }
    //    PrimarySurface = SDL_GetWindowSurface(Window);

    if ( (Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr ) {
        Log("Unable to create renderer");
        return false;
    }

    //SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

    // Initialize image loading for PNGs
    if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
        Log("Unable to init SDL_image: %s", IMG_GetError());
        return false;
    }

    // Load all of our Textures (see TextureBank class for expected folder)
    if ( TextureBank::Init() == false ) {
        Log("Unable to init TextureBank");
        return false;
    }

    //Check for joysticks
    if ( SDL_NumJoysticks() < 1 ) {
        printf("Warning: No joysticks connected!\n");
    } else {
        //Load joystick
        mJoystick = SDL_JoystickOpen(0);
        if ( mJoystick == NULL ) {
            logSDLError(std::cout, "CApp::OnInit");
        } else
            std::cout << "LOADED JOYSTICK" << std::endl;
    }


    for ( int i = 0; i < SDL_NumJoysticks(); ++i ) {
        if ( SDL_IsGameController(i) ) {
            mGameController = SDL_GameControllerOpen(i);
            if ( mGameController ) {
                cout << "Found Controller" << endl;
                std::cout << SDL_GameControllerMapping(mGameController) << std::endl;
                break;
            } else {
                logSDLError(std::cout, "CApp::OnInit");                
            }
        }
        else {
            std::cout << "not a Controller" << std::endl;
        }
    }

    // The Players
    Texture *texture = TextureBank::Get("somecharacters");
    if ( texture != nullptr ) {
        mPlayerPtr = std::make_shared<Player>();
        mPlayerPtr->setWidth(30);
        mPlayerPtr->setHeight(30);
    }
    
    // Game map
    

    return true;
}
// TODO: need to move this somewhere else

void App::shoot( ) {
    Mix_PlayChannel(-1, mPew, 0);
}

//------------------------------------------------------------------------------

void App::Loop( ) {
    if ( mGameController != nullptr && SDL_GameControllerGetAttached(mGameController) ) {
        // NOTE: We have a mGameController with index ControllerIndex.

        mPlayerPtr->handle_input(mGameController);
        mPlayerPtr->move();
        //mPlayerPtr->checkCollision(mNPCPtr->getCollider());

        //mPlayerPtr->updateBullets();
    }
}

//------------------------------------------------------------------------------

void App::Render( ) {
    SDL_RenderClear(Renderer);

    // std::cout << __FILE__ << " " << __LINE__ << std::endl;

    // TODO: need to loop through textures?
    Texture* texture = nullptr;

    // Background
//    texture = TextureBank::Get("tile");
//    if ( texture != nullptr ) {
//        for ( int x = 0; x < GetWindowWidth(); x += texture->GetWidth() ) {
//            for ( int y = 0; y < GetWindowHeight(); y += texture->GetHeight() ) {
//                texture->Render(x,y);
//            }
//        }
//    }
    
    texture = TextureBank::Get("tileset");
    for ( int row = 0; row < map.mapHeight; row++ ) {
        for ( int col = 0; col < map.mapWidth; col++ ) {
            // get tile #
            int tileNum = map.getTile(row,col);
            
            // translate to clip
            int tilecol = map.getClipX(tileNum);
            int tilerow = map.getClipY(tileNum);
            
            // Destination / Source
            //Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight)
                    
            // get texture
            texture->Render(col*32, row*32, 32, 32,
                    tilecol*32, tilerow*32, 32,32);
        }
    }
    
    

    // Players
    //texture = TextureBank::Get(mPlayerPtr->getSpriteName());
    texture = mPlayerPtr->getTexture(Renderer);
    
    if ( texture != nullptr ) {

        //SDL_Rect clip = mPlayerPtr->getClip();
        //texture->render(Renderer, mPlayerPtr->mPosX, mPlayerPtr->mPosY,
        //        &clip, mPlayerPtr->mFaceDirection);
    } else {
        logSDLError(std::cout, "App1::Render");
    }

    int width = 0;
    int height = 0;
    SDL_RenderGetLogicalSize(Renderer, &width, &height);
    //std::cout << "SDL_RenderGetLogicalSize " << width << " " << height << std::endl;

    // 4:3 aspect ratio resolutions:   640×480, 800×600, 960×720, 1024×768, 1280×960, 1400×1050, 1440×1080 , 1600×1200, 1856×1392, 1920×1440, and 2048×1536.
    // 16:10 aspect ratio resolutions: 1280×800, 1440×900, 1680×1050, 1920×1200 and 2560×1600.
    // 16:9 aspect ratio resolutions:  1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080, 2560×1440 and 3840×2160.
    
    // 4:3
    SDL_RenderSetLogicalSize(Renderer, 320, 240);
    //SDL_RenderSetLogicalSize(Renderer, 400, 300);
    //SDL_RenderSetLogicalSize(Renderer, 640, 480);
    //SDL_RenderSetLogicalSize(Renderer, 800, 600);
    //SDL_RenderSetLogicalSize(Renderer, 1024, 768);
    
    //SDL_RenderSetLogicalSize(Renderer, 1024, 576);
    //SDL_RenderSetLogicalSize(Renderer, 1280, 720);
    //SDL_RenderSetLogicalSize(Renderer, 1920, 1080);

    SDL_RenderGetLogicalSize(Renderer, &width, &height);
    //std::cout << "SDL_RenderGetLogicalSize " << width << " " << height << std::endl;
    SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------

void App::Cleanup( ) {

    TextureBank::Cleanup();

    if ( Renderer ) {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
    }

    if ( Window ) {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }

    // sounds?

    IMG_Quit();
    SDL_Quit();
}

//------------------------------------------------------------------------------

int App::Execute( int argc, char* argv[] ) {
    if ( !Init() ) return 0;

    SDL_Event Event;

    while (Running) {
        //Start the frame timer
        fps.start();


        while (SDL_PollEvent(&Event) != 0) {
            OnEvent(&Event);

            if ( Event.type == SDL_QUIT )
                Running = false;
        }

        Loop();
        Render();

        //Cap the frame rate
        if ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
        }

        //SDL_Delay(1); // Breath
    }

    Cleanup();

    return 1;
}

//==============================================================================

SDL_Renderer * App::GetRenderer( ) {
    return Renderer;
}

//==============================================================================

App * App::GetInstance( ) {
    return &App::Instance;
}

int App::GetWindowWidth( ) {
    int width;
    int height;
    SDL_RenderGetLogicalSize(GetInstance()->Renderer, &width, &height);

    //return SCREEN_WIDTH;
    return width;
}

int App::GetWindowHeight( ) {
    //return SCREEN_HEIGHT;

    int width;
    int height;
    SDL_RenderGetLogicalSize(GetInstance()->Renderer, &width, &height);

    //return SCREEN_WIDTH;
    return height;
}

//==============================================================================
