#include "Entity.h"

Entity::Entity(SpritePtr sprite)
: mSprite(sprite)
{

}

Entity::~Entity()
{

}

DRReturn Entity::move(float fTime)
{
	return DR_OK;
}

DRReturn Entity::render()
{
	glPushMatrix();
	glScalef(mScaling.x, mScaling.y, 1.0f);
	glTranslatef(mPosition.x, mPosition.y, 0.0f);
	mSprite->render();
	return DR_OK;
}