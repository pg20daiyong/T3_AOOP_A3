//
// + MissileEnemy.cpp
// missile of an enemy
//

#include "Game/Private/Game.h"
#include "Game/Private/MissileEnemy.h"
#include "Game/Private/Random.h"

#include "Engine/Public/EngineInterface.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const float gMissileEnemySpeed = 100.0f;
const float gMissileEnemyRadius = 25.0f;
const float gFuseMin = 0.5f;
const float gFuseMax = 1.5f;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MissileEnemy::MissileEnemy( exEngineInterface* pEngine, const exVector2& v2Position, bool bAlwaysFuse )
	: GameObject( pEngine, v2Position, gMissileEnemyRadius )
	, mLeft( false )
{
	// do we want a fuse?
	bool bFuse = false;

	if ( bAlwaysFuse )
	{
		bFuse = true;
	}
	else
	{
		const float fChance = RandomFloat( 0.0f, 1.0f );

		if ( fChance < 0.5f )
		{
			bFuse = true;
		}
	}

	// deal with the fuse request
	if ( bFuse )
	{
		mFuse = RandomFloat( gFuseMin, gFuseMax );

		mColor->mColor[0] = 0;
		mColor->mColor[0] = 0;
		mColor->mColor[3] = 255;
	}
	else
	{
		mFuse = -1.0f;
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MissileEnemy::~MissileEnemy()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MissileEnemy::Update( float fDeltaT )
{
	// do we have a fuse? if so, deal with it
	if ( mFuse >= 0.0f )
	{
		mFuse -= fDeltaT;

		if ( mFuse <= 0.0f )
		{
			extern MyGame gGame;
			gGame.CreateExplosion( mPosition );

			mExpiring = true;

			return;
		}
	}

	// go from side to side
	const float fPositionGapX = 60.0f;

	const float fPositionLeftX = fPositionGapX;
	const float fPositionRightX = kViewportWidth - fPositionGapX;

	if ( mPosition.x < fPositionLeftX )
	{
		mLeft = false;
	}
	else if ( mPosition.x > fPositionRightX )
	{
		mLeft = true;
	}

	exVector2 v2Velocity;
	v2Velocity.y = 0.0f;

	if ( mLeft )
	{
		v2Velocity.x = -1.0f;
	}
	else
	{
		v2Velocity.x = 1.0f;
	}

	v2Velocity.x *= gMissileEnemySpeed;

	mPosition.x += v2Velocity.x * fDeltaT;
}