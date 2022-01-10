//
// + GameObject.cpp
// simple GameObject
//

#include "Game/Private/GameObject.h"

#include "Engine/Public/EngineInterface.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

GameObject::GameObject( exEngineInterface* pEngine, const exVector2& v2Position, float fRadius )
	: mEngine( pEngine )
	, mPosition( v2Position )
	, mRadius( fRadius )
	, mExpiring( false )
{
	// this doesn't really need to be on the heap, but quickens the death of the program when the dangling pointers appear
	mColor = new exColor();

	mColor->mColor[0] = 255;
	mColor->mColor[1] = 255;
	mColor->mColor[2] = 255;
	mColor->mColor[3] = 255;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

GameObject::~GameObject()
{
	delete mColor;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void GameObject::Render()
{
	mEngine->DrawCircle( mPosition, mRadius, *mColor, 0 );
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void GameObject::Expire()
{
	mExpiring = true;
}
