//
// + GameObject.h
// simple GameObject
//

#pragma once

#include "Engine/Public/EngineTypes.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class exEngineInterface;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class GameObject
{
public:

	GameObject( exEngineInterface* pEngine, const exVector2& v2Position, float fRadius );
	~GameObject();

	virtual void Update( float fDeltaT ) = 0;

	void Render();

	void Expire();

public:

	exEngineInterface* mEngine;
	exVector2 mPosition;
	float mRadius;
	exColor* mColor;
	bool mExpiring;

};
