#pragma once
#pragma once
#include "Tower.h"
#include "GameObject.h"
#include "Projectile3.h"

class Tower3 : public Tower
{
	GameObject* target;
	CircleShape rangeCircle;
	int r = 35;
public:

	Tower3(Vector2f pos)
		:Tower(pos, "assets/tower3.png")
	{
		target = nullptr;
		range = 2000;
		attSpeed = 2.0f;
		countAttTime = 0.4f;

	}

	void update()
	{

		Vector2f center = getCenter();
		if (target != nullptr && Utils::get().distance(target->getPos().x, target->getPos().y, center.x, center.y) > range / 2)
		{
			target = nullptr;
		}
		if (target != nullptr && target->destroyFlag)
		{
			target = nullptr;
		}

	}

	void draw()
	{
		Tower::draw();
	}

	void setTarget(GameObject* target)
	{
		if (this->target != nullptr)
		{
			return;
		}
		Vector2f center = getCenter();
		if (Utils::get().distance(target->getPos().x, target->getPos().y, center.x, center.y) < range / 2)
		{
			this->target = target;
		}

	}


	void attack(vector<Projectile*>* projectiles)
	{

		countAttTime += Utils::get().deltaTime;
		if (countAttTime >= attSpeed)
		{
			countAttTime = 0;
			for (int i = 0; i < 360; i += r){
				Vector2f dir = Vector2f((float)cos(i), (float)sin(i));
				projectiles->push_back(new Projectile3(Vector2f(pos.x + getRect().width / 2 - 8, pos.y + 8), dir));
			}
		}

	}

	void upgrade() {
		upgraded = true;
		attSpeed = 1.0f;
		r = 20;

		texture.loadFromFile("assets/tower3Up.png");
		this->sprite.setTexture(texture);
	}

};