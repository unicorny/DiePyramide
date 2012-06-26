#include "MainGameState.h"

MainGameState::MainGameState()
: DRGameState(0.5f)
{
	mGameFont.init("data/introFont.tga", "data/introFont.tbf");
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
	printf("MainGameState::render firstState: %d\n", mFirstState);
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
