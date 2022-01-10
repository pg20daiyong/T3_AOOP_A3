#include "GameObjectHandle.h"

GameObjectHandle::GameObjectHandle(GameObject* gameObject)
	:mGameOjbect(gameObject)
{
}

bool GameObjectHandle::IsValid() const
{
	return mGameOjbect != nullptr;
}

GameObject* GameObjectHandle::GetGameObject() const
{
	return mGameOjbect;
}