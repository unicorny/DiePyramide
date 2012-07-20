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


#ifndef __PY_KI__
#define __PY_KI__

#include "parseXML.h"

class KI
{
public:
	KI();
	virtual ~KI();

	virtual DRVector2 getDir(float time, DRVector2 dir) = 0;

// static 
	static KI* createKI(tinyxml2::XMLElement* ki, const char* xmlFileName);
	static void destroyKI(KI* ki) {DR_SAVE_DELETE(ki);}
};

#endif __PY_KI__