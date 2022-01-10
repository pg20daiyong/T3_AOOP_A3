//
// + Explosion.cpp
// colourful explosion
//

#include "Game/Private/Explosion.h"
#include "Game/Private/Random.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const float gExplosionRadiusSpeed = 250.0f;
const float gExplosionRadiusStart = 40.0f;
const float gExplosionRadiusTarget = 135.0f;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

Explosion::Explosion( exEngineInterface* pEngine, const exVector2& v2Position )
	: GameObject( pEngine, v2Position, gExplosionRadiusStart )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

Explosion::~Explosion()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void Explosion::Update( float fDeltaT )
{
	mColor->mColor[0] = RandomInt( 255 );
	mColor->mColor[1] = RandomInt( 255 );
	mColor->mColor[2] = RandomInt( 255 );

	mRadius += gExplosionRadiusSpeed * fDeltaT;

	if ( mRadius > gExplosionRadiusTarget )
	{
		mExpiring = true;
	}
}