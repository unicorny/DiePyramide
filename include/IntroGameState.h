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

#ifndef __PY_INTRO_GAME_STATE__
#define __PY_INTRO_GAME_STATE__

#include "MainMenuGameState.h"

class IntroGameState : public DRGameState
{
public:
	IntroGameState();
	virtual ~IntroGameState();

	virtual DRReturn move(float fTime);
	virtual DRReturn render(float fTime);

	virtual const char* getResourceType() const {return "IntroGameState";}
	virtual bool less_than(DRIResource& tex) const
	{
		return false;//mTexturID <  dynamic_cast<DRTexture&>(tex).mTexturID;
	}
private:
	DRFont mIntroFont;
	float  mElapsedTime;
	DRTexturePtr mLogo;

	DRGameStatePtr mMainMenuGameState;
};

#endif //__PY_INTRO_GAME_STATE__