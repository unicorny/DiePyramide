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

#ifndef __PY_SPRITE_MANAGER__
#define __PY_SPRITE_MANAGER__

#include "Sprite.h"

class SpriteManager
{
public:
	~SpriteManager();
	static SpriteManager& Instance();
	inline static SpriteManager& getSingleton() {return Instance();};
	inline static SpriteManager* getSingletonPtr() {return &Instance();};
	static bool	isInitialized()	{return Instance().mInitalized;};

	void exit();
	DRReturn init();

	SpritePtr getSprite(const char* filename);

	DRReturn renderSprite() {if(!mInitalized) LOG_ERROR("not initalized!", DR_ERROR); return mSpriteGeometrie->render();}

private:
	SpriteManager();

	bool mInitalized;

	DRSpriteGeometriePtr mSpriteGeometrie;
	std::map<DHASH, SpritePtr> mSprites;
	typedef std::pair<DHASH, SpritePtr> SPRITE_PAIR;
};

#endif //__PY_SPRITE_MANAGER__