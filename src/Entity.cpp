#include "Entity.h"
#include "SpriteManager.h"

Entity::Entity(tinyxml2::XMLElement* entity, KI* ki, const char* xmlFileName)
: mPosition(0.0f), mScaling(1.0f), mDelta(0.0f), mKI(ki)
{
    XML::parseVector2(entity, "startPos", mPosition, xmlFileName);
    XML::parseFloat(entity, "delta", mDelta, xmlFileName);
    DRString textureName;
    XML::parseText(entity, "texture", textureName, xmlFileName);
    mSprite = SpriteManager::Instance().getSprite(textureName.data());
    XML::parseVector2(entity, "scale", mScaling, xmlFileName);
}

Entity::~Entity()
{
}

DRReturn Entity::move(float fTime)
{
    if(mKI) 
    {
        mPosition += mKI->getDir(fTime, mPosition);
        if(mPosition.x < 0.0f) mPosition.x = 0.0f;
        if(mPosition.x > 1.0f) mPosition.x = 1.0f;
        if(mPosition.y < 0.0f) mPosition.y = 0.0f;
        if(mPosition.y > 1.0f) mPosition.y = 1.0f;
    }
    return DR_OK;
}

DRReturn Entity::render()
{
    glPushMatrix();
    glScalef(mScaling.x, mScaling.y, 1.0f);
    glTranslatef(mPosition.x, mPosition.y, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    mSprite->render();
    glPopMatrix();
    return DR_OK;
}