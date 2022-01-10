//
// + MissileEnemy.h
// missile of an enemy
//

#pragma once

#include "Game/Private/GameObject.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MissileEnemy : public GameObject
{
public:

	MissileEnemy( exEngineInterface* pEngine, const exVector2& v2Position, bool bAlwaysFuse );
	~MissileEnemy();

	virtual void Update( float fDeltaT ) override;

private:

	bool mLeft;
	float mFuse;

};