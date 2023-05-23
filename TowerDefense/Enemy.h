#pragma once
#include "GameObject.h"
#include "Healthbar.h"
class Enemy : public GameObject
{
protected:
	int health = 3;
	HealthBar healthbar;

	
public:

	Enemy(Vector2f pos) : GameObject(pos)
	{
		this->type = GameObject::ENEMY;
	}


	void update()
	{


	}

	void draw() {
		GameObject::draw();
		healthbar.draw(health, Vector2f(pos.x, pos.y - 5));
	}

	virtual void damage(int damage)
	{

	}

};