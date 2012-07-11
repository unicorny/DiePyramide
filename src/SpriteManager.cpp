#include "SpriteManager.h"

SpriteManager::SpriteManager()
: mInitalized(false)
{

}

SpriteManager::~SpriteManager()
{
    if(mInitalized) exit();
}

SpriteManager& SpriteManager::Instance()
{
    static SpriteManager TheOneAndOnly;
    return TheOneAndOnly;
}

DRReturn SpriteManager::init()
{
    if(mInitalized) return DR_OK;

    mSpriteGeometrie = DRSpriteGeometriePtr(new SpriteGeometrie);
    mGetSpriteMutex = SDL_CreateMutex(); LOG_WARNING_SDL();

    LOG_INFO("SpriteManager initalized");
    mInitalized = true;
    return DR_OK;
}

void SpriteManager::exit()
{
    if(!mInitalized) return;
    mSprites.clear();
    SDL_LockMutex(mGetSpriteMutex); LOG_WARNING_SDL();
    SDL_UnlockMutex(mGetSpriteMutex); LOG_WARNING_SDL();
    SDL_DestroyMutex(mGetSpriteMutex); LOG_WARNING_SDL();
    LOG_INFO("SpriteManager closed");
    mInitalized = false;
}

SpritePtr SpriteManager::getSprite(const char* filename)
{
    DHASH id = DRMakeFilenameHash(filename);
    SDL_LockMutex(mGetSpriteMutex); LOG_WARNING_SDL();
    if(mSprites.find(id) != mSprites.end())
    {
        SDL_UnlockMutex(mGetSpriteMutex); LOG_WARNING_SDL();
        return mSprites[id];
    }
    SpritePtr sprite(new Sprite(filename));
    mSprites.insert(SPRITE_PAIR(id, sprite));
    SDL_UnlockMutex(mGetSpriteMutex); LOG_WARNING_SDL();
    return sprite;
}