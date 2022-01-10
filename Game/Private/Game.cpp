//
// * ENGINE-X
// * MISSILE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Private/MissileEnemy.h"
#include "Game/Private/MissileHoming.h"
#include "Game/Private/Explosion.h"

#include <time.h>

#include <algorithm>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Missile Game";

const float gMissileEnemyRespawnTime = 1.0f;
const float gMissileHomingIntervalTime = 2.0f;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mRelease( false )
	, mTimeMissileEnemy( 0.0f )
	, mTimeHomingEnemy( 0.0f )
	, mFirstEnemyMissile( true )
	, mEnemyMissile( nullptr )
	, mWasEnemyMissile( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	srand( (unsigned int)time( 0 ) );
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	mRelease = pState[SDL_SCANCODE_SPACE];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	//
	// run game logic simulation
	//

	// deal with enemy missile
	if ( mEnemyMissile != nullptr )
	{
		mWasEnemyMissile = true;
	}
	else
	{
		if ( mWasEnemyMissile )
		{
			mTimeMissileEnemy = gMissileEnemyRespawnTime;

			mWasEnemyMissile = false;
		}

		mTimeMissileEnemy -= fDeltaT;

		if ( mTimeMissileEnemy <= 0.0f )
		{
			exVector2 v2EnemyMissileStart;
			v2EnemyMissileStart.x = kViewportWidth * 0.5f;
			v2EnemyMissileStart.y = kViewportHeight * 0.25f;

			GameObject* pMissileEnemy = new MissileEnemy( mEngine, v2EnemyMissileStart, mFirstEnemyMissile );
			mGameObjects.push_back( new GameObjectHandle(pMissileEnemy) );

			mTimeMissileEnemy = 0.0f;

			mFirstEnemyMissile = false;
			mEnemyMissile = pMissileEnemy;
		}
	}

	// deal with firing homing missile
	mTimeHomingEnemy -= fDeltaT;

	if ( mTimeHomingEnemy < 0.0f )
	{
		mTimeHomingEnemy = 0.0f;
	}

	if ( mRelease && mTimeHomingEnemy <= 0.0f && mEnemyMissile != nullptr )
	{
		exVector2 v2HomingMissileStart;
		v2HomingMissileStart.x = kViewportWidth * 0.5f;
		v2HomingMissileStart.y = kViewportHeight * 0.8f;

		GameObject* pMissileHoming = new MissileHoming( mEngine, v2HomingMissileStart, mEnemyMissile );
		mGameObjects.push_back(new GameObjectHandle(pMissileHoming));

		mTimeHomingEnemy = gMissileHomingIntervalTime;
	}
	
	//
	// game object management
	//

	// update objects first
	for ( GameObjectHandle* pGameObject : mGameObjects )
	{
		if ( !pGameObject->GetGameObject()->mExpiring )
		{
			pGameObject->GetGameObject()->Update( fDeltaT );
		}
	}

	// deal with expired objects first
	// TODO - explain why we're adding to a separate list first

	std::vector<GameObjectHandle*> gameObjectsToRemove;

	for (GameObjectHandle* pGameObject : mGameObjects )
	{
		if ( pGameObject->GetGameObject()->mExpiring )
		{
			gameObjectsToRemove.push_back(pGameObject);
		}
	}

	for (GameObjectHandle* pGameObject : gameObjectsToRemove )
	{
		mGameObjects.erase( std::remove( mGameObjects.begin(), mGameObjects.end(), pGameObject ), mGameObjects.end() );
		delete pGameObject;
	}
	
	// add all new objects
	// TODO - explain why we're doing this as a separate step

	for (GameObjectHandle* pGameObject : mGameObjectsToAdd )
	{
		mGameObjects.push_back(pGameObject);
	}

	mGameObjectsToAdd.clear();

	// now render everything
	for (GameObjectHandle* pGameObject : mGameObjects )
	{
		pGameObject->GetGameObject()->Render();
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::CreateExplosion( exVector2 v2Position )
{
	GameObject* pExplosion = new Explosion( mEngine, v2Position );
	mGameObjectsToAdd.push_back(new GameObjectHandle(pExplosion) );
}