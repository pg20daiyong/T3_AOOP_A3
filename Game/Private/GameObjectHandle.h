#pragma once

class GameObject;

class GameObjectHandle
{
public:
	GameObjectHandle(GameObject* gameObject);

	bool IsValid() const;
	
	GameObject* GetGameObject() const;

private:
	GameObject* mGameOjbect;

};