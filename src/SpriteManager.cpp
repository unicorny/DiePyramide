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

	LOG_INFO("SpriteManager initalized");
	mInitalized = true;
	return DR_OK;
}

void SpriteManager::exit()
{
	if(!mInitalized) return;
	mSprites.clear();
	LOG_INFO("SpriteManager closed");
	mInitalized = false;
}

SpritePtr SpriteManager::getSprite(const char* filename)
{
	DHASH id = DRMakeFilenameHash(filename);
	if(mSprites.find(id) != mSprites.end())
	{
		return mSprites[id];
	}
	SpritePtr sprite(new Sprite(filename));
	mSprites.insert(SPRITE_PAIR(id, sprite));
	return sprite;
}