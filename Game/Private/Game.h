//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"

#include <vector>
#include "GameObjectHandle.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class GameObject;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

	void						CreateExplosion( exVector2 v2Position );

public:

	exEngineInterface*			mEngine;

	bool						mRelease;

	float						mTimeMissileEnemy;
	float						mTimeHomingEnemy;

	bool						mFirstEnemyMissile;
	GameObject*					mEnemyMissile;
	bool						mWasEnemyMissile;

	std::vector<GameObjectHandle*>	mGameObjects;
	std::vector<GameObjectHandle*>	mGameObjectsToAdd;

};
