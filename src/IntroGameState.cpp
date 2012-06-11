#include "IntroGameState.h"

IntroGameState::IntroGameState()
: DRGameState(1.0f), mElapsedTime(0.0f), mMainMenuGameState(new MainMenuGameState)
{
	mIntroFont.init("data/introFont.tga", "data/introFont.tbf");
	mLogo = DRTextureManager::Instance().getTexture("data/img/logo.jpg", true);
	g_pGameStateManager->addConstantState(mMainMenuGameState, "MainMenu");
}

IntroGameState::~IntroGameState()
{
}

DRReturn IntroGameState::move(float fTime)
{
	mElapsedTime += fTime;
	//if(mElapsedTime >= 6.0f)
	{
		g_pGameStateManager->popState();
		g_pGameStateManager->pushState("MainMenu");
	}
	return DR_OK;
}

DRReturn IntroGameState::render(float fTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.2f, 0.1f, 0.15f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1.0f, 1.0f, 0.0f, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);	

	glColor3f(1.0f, 1.0f, 1.0f);
	//glTranslatef(0.0f, 0.0f, -1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	mLogo->bind();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	float step = mElapsedTime/4.0f;
	if(step > 0.5f) step = 0.5f;
	glTranslatef(step-0.5f, 0.0f, 0.0f);
	//unicorn
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.25f);
		glTexCoord2f(0.0f, 0.5f); glVertex2f(0.0f, 0.75f);
		glTexCoord2f(1.0f, 0.5f); glVertex2f(0.5f, 0.75f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.25f);
	glEnd();
	glLoadIdentity();
	if(step >= 0.5f)
	{
		step = mElapsedTime/4.0f-0.5f;
	}
	else step = 0.0f;
	if(step >= 0.5f) step = 0.5f;
	
	glTranslatef(-step+0.5f, 0.0f, 0.0f);
	//games
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.5f); glVertex2f(0.5f, 0.3f);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(0.5f, 0.8f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.8f);
		glTexCoord2f(1.0f, 0.5f); glVertex2f(1.0f, 0.3f);
	glEnd();
//*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

/*	mIntroFont.begin();
	DRText text(&mIntroFont);
	text.setText("Elapsed Time: %f", mElapsedTime);
	text.setFlags(DR_FF_RELATIVE | DR_FF_RELATIVSCALING);
	text.setScaling(DRVector2(1.4f, 1.4f));
	text.drawText();
	mIntroFont.end();
//	*/
	return DR_OK;
}