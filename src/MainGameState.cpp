#include "MainGameState.h"
#include "SpriteManager.h"

MainGameState::MainGameState()
: DRGameState(0.5f)
{
	mGameFont.init("data/introFont.tga", "data/introFont.tbf");
	mBackgroundImage = DRTextureManager::Instance().getTexture("Pyramide.jpg", true);

	//read entity via xml 
}

MainGameState::~MainGameState()
{

}

DRReturn MainGameState::render(float fTime)
{
    if(mFirstState)
    {
        glClearColor(0.1f, 0.6f, 0.74f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.2f, 0.1f, 0.15f, 1.0f);
    }

	// background
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	mBackgroundImage->bind();
	glColor3f(1.0f, 1.0f, 1.0f);
	SpriteManager::Instance().renderSprite();



	return DR_OK;
}

DRReturn MainGameState::move(float fTime)
{
	if(EnIsButtonPressed(SDLK_ESCAPE))
	{
		g_pGameStateManager->pushState("MainMenu");
	}
	return DR_OK;
}
