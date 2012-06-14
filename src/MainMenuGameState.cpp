#include "MainMenuGameState.h"

MainMenuGameState::MainMenuGameState()
: DRGameState(0.5f), mMainGameState(new MainGameState)
{
	mMenuFont.init("data/introFont.tga", "data/introFont.tbf");
	// place for multilanguage
	mMenuEntrys.push_back(MainMenuEntry("Spiel beenden", EXIT_GAME));
	mMenuEntrys.push_back(MainMenuEntry("Neues Spiel starten", NEW_GAME));
	mMenuEntrys.push_back(MainMenuEntry("Hilfe", HELP_WITH_GAME));
	updateMenuEntrys();
	mMenuEntrys.front().choosen = true;

	g_pGameStateManager->addConstantState(mMainGameState, "Game");
}

MainMenuGameState::~MainMenuGameState()
{

}

DRReturn MainMenuGameState::render(float fTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.2f, 0.1f, 0.15f, 1.0f);
	glClearColor(0.404f, 0.525f, 0.643f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1.0f, 1.0f, 0.0f, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glDisable(GL_TEXTURE_2D);

	u8 alpha = static_cast<u8>(mTransparency*255.0f);
	DRColor sand(205, 175, 142, alpha);
	DRColor sandChoosen(205, 197, 176, alpha);

	for(std::list<MainMenuEntry>::iterator it = mMenuEntrys.begin(); it != mMenuEntrys.end(); it++)
	{
		if(it->choosen)
			glColor4fv(sandChoosen);
		else
			glColor4fv(sand);
		DRVector2 edge1 = it->topLeftPoint;
		DRVector2 edge2 = it->bottomRightPoint;
		glBegin(GL_QUADS);
			glVertex2f(edge1.x, edge1.y);
			glVertex2f(edge1.x, edge2.y);
			glVertex2f(edge2.x, edge2.y);
			glVertex2f(edge2.x, edge1.y);
		glEnd();
	}
	alpha = 255;
	DRColor textColor(41, 56, 203, alpha);
	DRColor choosenTextColor(29, 38, 121, alpha);

	mMenuFont.begin();
	DRText text(&mMenuFont);
	text.setFlags(DR_FF_RELATIVE | DR_FF_RELATIVSCALING | DR_FF_ALIGN_VCENTER | DR_FF_ALIGN_HCENTER);
	for(std::list<MainMenuEntry>::iterator it = mMenuEntrys.begin(); it != mMenuEntrys.end(); it++)
	{
		if(it->choosen)
			text.setColor12(textColor);
		else
			text.setColor12(choosenTextColor);

		DRVector2 edge1 = it->topLeftPoint;
		DRVector2 edge2 = it->bottomRightPoint;

		text.setText(it->name.data());
		text.setPosition(edge1+(edge2-edge1)/2.0f);
		text.setScaling(DRVector2(1.2f, 1.2f));
		text.drawText();
	}	
	mMenuFont.end();

	

	return DR_OK;
}

DRReturn MainMenuGameState::move(float fTime)
{
	if(EnIsButtonPressed(SDLK_ESCAPE)) menuAction(EXIT_GAME);

	std::list<MainMenuEntry>::iterator it = getChoosenEntry();

	// cursor down
	if(EnIsButtonPressed(SDLK_DOWN) || EnIsButtonPressed(SDLK_s))
	{
		it->choosen = false;
		it++;
		if(it == mMenuEntrys.end())
			it = mMenuEntrys.begin();
		it->choosen = true;
	}
	// cursor up
	if(EnIsButtonPressed(SDLK_UP) || EnIsButtonPressed(SDLK_w))
	{
		it->choosen = false;
		if(it == mMenuEntrys.begin())
			it = mMenuEntrys.end();
		it--;
		it->choosen = true;
	}

	// choose with mouse
	int x, y;
	Uint8 mouseState = SDL_GetMouseState(&x, &y);
	DRVector2 mousePos(static_cast<float>(x)/static_cast<float>(XWIDTH),
					   static_cast<float>(y)/static_cast<float>(YHEIGHT));
	for(std::list<MainMenuEntry>::iterator it = mMenuEntrys.begin(); it != mMenuEntrys.end(); it++)
	{
		if(mousePos.x > it->topLeftPoint.x && mousePos.x < it->bottomRightPoint.x &&
		   mousePos.y > it->topLeftPoint.y && mousePos.y < it->bottomRightPoint.y)
		{
			getChoosenEntry()->choosen = false;
			it->choosen = true;
			break;
		}
	}

	// enter
	if(EnIsButtonPressed(SDLK_RETURN) || mouseState & SDL_BUTTON(1))
	{
		menuAction(it->menuFunction);
	}

	return DR_OK;
}

std::list<MainMenuEntry>::iterator MainMenuGameState::getChoosenEntry()
{
	for(std::list<MainMenuEntry>::iterator it = mMenuEntrys.begin(); it != mMenuEntrys.end(); it++)
	{
		if(it->choosen)
		{
			return it;
		}
	}
	return mMenuEntrys.end();
}

void MainMenuGameState::updateMenuEntrys()
{
	mMenuEntrys.sort();
	float count = 0.0f;
	float height = 0.8f / static_cast<float>(mMenuEntrys.size());
	for(std::list<MainMenuEntry>::iterator it = mMenuEntrys.begin(); it != mMenuEntrys.end(); it++)
	{
		it->topLeftPoint = DRVector2(0.2f, 0.1f+(count+0.25f)*height);
		it->bottomRightPoint = DRVector2(0.8f, it->topLeftPoint.y + height*0.5f);

		count+= 1.0f;
	}
}

void MainMenuGameState::menuAction(MenuFunction menuFunction)
{
	switch(menuFunction)
	{
	case EXIT_GAME:
		EnPostExitMessageToSDL();
		break;
	case NEW_GAME:
		g_pGameStateManager->popState();
		if(g_pGameStateManager->getStateCount() == 0)
			g_pGameStateManager->pushState("Game");
		break;
	default: LOG_WARNING("unknown function");
	}
}