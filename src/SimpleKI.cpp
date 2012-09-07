#include "SimpleKI.h"

SimpleKI::SimpleKI(tinyxml2::XMLElement* ki, const char* xmlFileName)
: mXDir(0.0f), mYDir(0.0f), mSpeed(0.0f), mChangeDir(0.0f)
{
    XML::parseVector2(ki, "XDir", mXDir, xmlFileName);
    XML::parseVector2(ki, "YDir", mYDir, xmlFileName);
    XML::parseFloat(ki, "speed", mSpeed, xmlFileName);
	XML::parseFloat(ki, "changeDir", mChangeDir, xmlFileName);
}

SimpleKI::~SimpleKI()
{
}

DRVector2 SimpleKI::getDir(DRVector2 dir)
{
    //printf("\r rand: %f", DRRandom::core2_randf());
    DRVector2 move(dir);
	if(DRRandom::core2_randf() <= mChangeDir)
	{
		if(DRRandom::core2_randf() <= mXDir.x) 
			move.x += DRRandom::core2_randf();
		if(DRRandom::core2_randf() <= mXDir.y)
			move.x -= DRRandom::core2_randf();

		if(DRRandom::core2_randf() <= mYDir.x) 
			move.y += DRRandom::core2_randf();
		if(DRRandom::core2_randf() <= mYDir.y)
			move.y -= DRRandom::core2_randf();
	}
	//Vorzeichen
	DRVector2 precedingSign(1.0f);
	if(move.x < 0.0f) precedingSign.x = -1.0f;
	if(move.y < 0.0f) precedingSign.y = -1.0f;
    move = move.normalizeEx()*mSpeed;
	printf("\r precedingSign: %f, %f", precedingSign.x, precedingSign.y);
    return move;
}