//
// + Explosion.h
// colourful explosion
//

#pragma once

#include "Game/Private/GameObject.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class Explosion : public GameObject
{
public:

	Explosion( exEngineInterface* pEngine, const exVector2& v2Position );
	~Explosion();

	virtual void Update( float fDeltaT ) override;

};