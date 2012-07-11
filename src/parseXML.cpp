#include "ParseXML.h"

namespace XML
{
    DRReturn parseText(tinyxml2::XMLElement* ele, const char* name, DRString& text, const char* xmlFileName)
    {
        char buffer[64];
        if(strlen(name) > 43) LOG_ERROR("name to long", DR_ERROR);
        tinyxml2::XMLElement* element = ele->FirstChildElement(name);
        sprintf(buffer, "%s didn't exist", name);
        if(!element) LOG_XML_ERROR(buffer, xmlFileName, DR_ERROR);
        const char* ctext = element->GetText();
        sprintf(buffer, "%s didn't contain text", name);
        if(!ctext) LOG_XML_ERROR(buffer, xmlFileName, DR_ERROR);
        text = ctext;    
        
        return DR_OK;
    }

    DRReturn parseVector2(tinyxml2::XMLElement* ele, const char* name, DRVector2 &vec, const char* xmlFileName)
    {
        DRString text;
        if(parseText(ele, name, text, xmlFileName))
            LOG_ERROR("error by parse Text", DR_ERROR);
        sscanf(text.data(), "%f, %f", &vec.x, &vec.y);

        return DR_OK;
    }

    DRReturn parseFloat(tinyxml2::XMLElement* ele, const char* name, float &value, const char* xmlFileName)
    {
        DRString text;
        if(parseText(ele, name, text, xmlFileName))
            LOG_ERROR("error by parse Text", DR_ERROR);
        sscanf(text.data(), "%f", &value);

        return DR_OK;
    }
};