#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
protected:

	GameObject* target;
	float countDeadTime = 0;
	float deathTime = 1.0f;

public: 
	
	Projectile(Vector2f pos)
		:GameObject(pos)
	{
		type = GameObject::PROJECTILE;
	}


	void update()
	{

		countDeadTime += Utils::get().deltaTime;
		if (countDeadTime >= deathTime)
		{
			destroyFlag = true;
		}
	}
};