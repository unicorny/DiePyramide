#include "KI.h"
#include "SimpleKI.h"

KI::KI()
{
}

KI::~KI()
{
}

KI* KI::createKI(tinyxml2::XMLElement* ki, const char* xmlFileName)
{
    KI* tempKI = NULL;
    //Simple KI
    if(ki->Attribute("class", "SimpleKI"))
    {
        tempKI = new SimpleKI(ki, xmlFileName);
    }
    return tempKI;
}