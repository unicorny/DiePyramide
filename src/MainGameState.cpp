#include "MainGameState.h"
#include "SpriteManager.h"

MainGameState::MainGameState()
: DRGameState(0.5f), mCurrentLevel(NULL), mLevelToLoad(NULL), mLoadThread(NULL), mLevelLoadMutex(NULL)
{
    mGameFont.init("data/introFont.tga", "data/introFont.tbf");
    
    mLevelLoadMutex = SDL_CreateMutex();
    mLevelToLoad = new Level("data/level/1.xml");
    mLoadThread = SDL_CreateThread(MainGameState::LevelLoadThread, this);
    LOG_WARNING_SDL();    
}

MainGameState::~MainGameState()
{
    //! wait for load thread to complete
    if(mLoadThread) SDL_WaitThread(mLoadThread, NULL);
    SDL_DestroyMutex(mLevelLoadMutex);
    LOG_WARNING_SDL();
    DR_SAVE_DELETE(mLevelToLoad);
    DR_SAVE_DELETE(mCurrentLevel);
}

DRReturn MainGameState::render(float fTime)
{
    if(mFirstState)
    {
        glClearColor(0.1f, 0.6f, 0.74f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.2f, 0.1f, 0.15f, 1.0f);
    }
    if(mCurrentLevel) mCurrentLevel->render(fTime);
    return DR_OK;
}

DRReturn MainGameState::move(float fTime)
{
    if(!mCurrentLevel && mLoadThread)
    {
        int result;
        SDL_WaitThread(mLoadThread, &result);
        mLoadThread = NULL;
        if(result) LOG_ERROR("Fehler by load Level", DR_ERROR);
        mCurrentLevel = mLevelToLoad;
        mLevelToLoad = NULL;
    }
    if(EnIsButtonPressed(SDLK_ESCAPE))
    {
        g_pGameStateManager->pushState("MainMenu");
    }
    if(mCurrentLevel) mCurrentLevel->move(fTime);
    return DR_OK;
}

int MainGameState::LevelLoadThread(void* data)
{
    MainGameState* t = static_cast<MainGameState*>(data);
    int returnValue = 0;
    SDL_LockMutex(t->mLevelLoadMutex);
    if(t->mLevelToLoad) 
        returnValue = t->mLevelToLoad->load();
    SDL_UnlockMutex(t->mLevelLoadMutex);
    return returnValue;
}