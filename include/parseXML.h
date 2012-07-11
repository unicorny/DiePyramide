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

#ifndef __DR_PARSE_XML__
#define __DR_PARSE_XML__

#include "Engine2Main.h"
#include "tinyxml2.h"
#define LOG_XML_ERROR(text, file, r) {DREngineLog.writeToLogDirect("<tr><td><font size=\"2\"><b><font color=\"#46fbe8\">XML Parse Error:</font></b> %s</font></td><td><font size=\"2\">(XML File: <i>%s</i>)</font></td></tr>", text, file); return r;}
#define LOG_XML_WARNING(text, file) {DREngineLog.writeToLogDirect("<tr><td><font size=\"2\"><b><font color=\"#46fbe8\">XML Parse Warning:</font></b> %s</font></td><td><font size=\"2\">(XML File: <i>%s</i>)</font></td></tr>", text, file);}

namespace XML
{
    DRReturn parseText(tinyxml2::XMLElement* ele, const char* name, DRString& text, const char* xmlFileName = "");
    DRReturn parseVector2(tinyxml2::XMLElement* ele, const char* name, DRVector2 &vec, const char* xmlFileName = "");
    DRReturn parseFloat(tinyxml2::XMLElement* ele, const char* name, float& value, const char* xmlFileName = "");
};

#endif //__DR_PARSE_XML__