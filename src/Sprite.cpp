#include "Sprite.h"
#include "SpriteManager.h"

SpriteGeometrie::SpriteGeometrie()
{
	init(4, 4, 1);
	mVertices[0] = DRVector3(0.0f, 0.0f, 0.0f);
	mVertices[1] = DRVector3(0.0f, 1.0f, 0.0f);
	mVertices[2] = DRVector3(1.0f, 1.0f, 0.0f);
	mVertices[3] = DRVector3(1.0f, 0.0f, 0.0f);
	mTextureCoords[0][0] = DRVector2(0.0f, 1.0f);
	mTextureCoords[0][1] = DRVector2(0.0f, 0.0f);
	mTextureCoords[0][2] = DRVector2(1.0f, 0.0f);
	mTextureCoords[0][3] = DRVector2(1.0f, 1.0f);
	mIndices[0] = 0;
	mIndices[1] = 1;
	mIndices[2] = 2;
	mIndices[3] = 3;
	mVertexCount = 4;
	mIndexCount = 4;

	setRenderMode(GL_QUADS);
}

SpriteGeometrie::~SpriteGeometrie()
{

}


Sprite::Sprite(const char* spriteFileName)
{
	mSpriteTexture = DRTextureManager::Instance().getTexture(spriteFileName, true);
}

Sprite::~Sprite()
{

}

DRReturn Sprite::render()
{
	glEnable(GL_TEXTURE_2D);
	mSpriteTexture->bind();
	return SpriteManager::Instance().renderSprite();
}