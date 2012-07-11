#include "SimpleKI.h"

SimpleKI::SimpleKI(tinyxml2::XMLElement* ki, const char* xmlFileName)
: mXDir(0.0f), mYDir(0.0f), mSpeed(0.0f)
{
    XML::parseVector2(ki, "XDir", mXDir, xmlFileName);
    XML::parseVector2(ki, "YDir", mYDir, xmlFileName);
    XML::parseFloat(ki, "speed", mSpeed, xmlFileName);
}

SimpleKI::~SimpleKI()
{
}

DRVector2 SimpleKI::getDir(float time, DRVector2 dir)
{
    printf("\r rand: %f", DRRandom::core2_randf());
    DRVector2 move(0.0f);
    if(DRRandom::core2_randf() <= mXDir.x) 
        move.x += DRRandom::core2_randf();
    if(DRRandom::core2_randf() <= mXDir.y)
        move.x -= DRRandom::core2_randf();
    if(DRRandom::core2_randf() <= mYDir.x) 
        move.y += DRRandom::core2_randf();
    if(DRRandom::core2_randf() <= mYDir.y)
        move.y -= DRRandom::core2_randf();
    move = move.normalizeEx()*mSpeed;
    return move;
}