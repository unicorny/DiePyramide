#include "main.h"
#include "time.h"
#include "IntroGameState.h"
#include "SpriteManager.h"


DRReturn load()
{
    if(EnInit_INI("data/config.ini"))
	    LOG_ERROR("Fehler bei init OpenGL", DR_ERROR);
    SDL_ShowCursor(true);
    DRRandom::seedf(time(NULL));
    SpriteManager::Instance().init();
    DRFileManager::Instance().addOrdner("data");
    DRFileManager::Instance().addOrdner("data/img");
    DRFileManager::Instance().addOrdner("data/img/wesen");
    return DR_OK;
}

void exit()
{
    SpriteManager::Instance().exit();
    EnExit();
}

#ifdef _WIN32
#undef main
#endif

int main()
{
    if(load())
    {
        printf("error by load\n");
        exit();
        return -1;
    }
    if(EnGameLoop(DRGameStatePtr(new IntroGameState), false))
    {
        printf("error in gameLoop\n");
        exit();
        return -1;
    }//*/
    exit();
    return 42;
}
