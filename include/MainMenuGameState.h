/*/*************************************************************************
 *                                                                         *
 * DiePyramide, it is a simple game										   *
 * Copyright (C) 2012, 2013, 2014 Dario Rekowski                           *
 * Email: dario.rekowski@gmx.de   Web: www.einhornimmond.de                *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * any later version.                                                      *
 *																		   * 
 * This program is distributed in the hope that it will be useful,	       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	       *
 * GNU General Public License for more details.				               *
 *									                                       *	
 * You should have received a copy of the GNU General Public License	   *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 ***************************************************************************/

#ifndef __PY_MAIN_MENU_GAME_STATE__
#define __PY_MAIN_MENU_GAME_STATE__

#include "MainGameState.h"

enum MenuFunction
{
	NOTHING = 0,
	NEW_GAME = 1,
	CONTINUE_GAME = 2,
	LOAD_GAME = 3,
	HELP_WITH_GAME = 4,
	SAVE_GAME = 5,	
	EXIT_GAME = 6
}; 

struct MainMenuEntry
{
	MainMenuEntry(const char* _name, MenuFunction _menuFunction)
		: name(_name), menuFunction(_menuFunction), topLeftPoint(0.0f), bottomRightPoint(0.0f),
		  choosen(false) {}

	//copy constructor
	MainMenuEntry(const MainMenuEntry& other) 
		: name(other.name), menuFunction(other.menuFunction), topLeftPoint(other.topLeftPoint),
		bottomRightPoint(other.bottomRightPoint), choosen(other.choosen) {}
	DRString name;
	MenuFunction menuFunction;
	DRVector2 topLeftPoint;
	DRVector2 bottomRightPoint;
	bool	  choosen;

	bool operator< (const MainMenuEntry &rhs) const { 
		return menuFunction < rhs.menuFunction;
	}
};

class MainMenuGameState : public DRGameState
{
public:
	MainMenuGameState();
	virtual ~MainMenuGameState();

	virtual DRReturn move(float fTime);
	virtual DRReturn render(float fTime);

	virtual const char* getResourceType() const {return "MainMenuGameState";}

	virtual bool less_than(DRIResource& tex) const
	{
		return false;//mTexturID <  dynamic_cast<DRTexture&>(tex).mTexturID;
	}
private:
	void updateMenuEntrys();
	void menuAction(MenuFunction menuFunction);

	std::list<MainMenuEntry>::iterator getChoosenEntry();

	DRFont mMenuFont;
	std::list<MainMenuEntry> mMenuEntrys;
	DRGameStatePtr	mMainGameState;
};

#endif //__PY_MAIN_MENU_GAME_STATE__
