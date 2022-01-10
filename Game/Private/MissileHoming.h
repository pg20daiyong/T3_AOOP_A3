//
// + MissileHoming.h
// missile to find enemy missile
//

#pragma once

#include "Game/Private/GameObject.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MissileHoming : public GameObject
{
public:

	MissileHoming( exEngineInterface* pEngine, const exVector2& v2Position, GameObject* pTarget );
	~MissileHoming();

	virtual void Update( float fDeltaT ) override;

private:

	GameObject* mTarget;
	float mStartingDistance;

};