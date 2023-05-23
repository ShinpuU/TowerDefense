#pragma once
#include "Tower.h"
#include "GameObject.h"
#include "Projectile1.h"

class Tower1 : public Tower
{
	GameObject* target;
	CircleShape rangeCircle;
public:

	Tower1(Vector2f pos)
		:Tower(pos, "assets/tower1.png")
	{
		target = nullptr;
		range = 200;
		attSpeed = 0.5f;
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
		/*if (getRect().contains(Utils.get().mousePos)) {
			Vector2 center = new Vector2(pos.X + rect.Width / 2, pos.Y + rect.Height / 2);
			Vector2 circlePos = new Vector2(center.X - range / 2, center.Y - range / 2);
			Utils.get().batch.Draw(circle, circlePos, Color.White);
		}*/

	}

	/*FloatRect getRect()
	{
		return FloatRect((int)pos.X, (int)pos.Y, rect.Width, rect.Height);
	}*/

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
		if (target == nullptr)
		{
			return ;
		}

		countAttTime += Utils::get().deltaTime;
		if (countAttTime >= attSpeed)
		{
			countAttTime = 0;
			projectiles->push_back( new Projectile1(Vector2f(pos.x + getRect().width / 2 - 4, pos.y + 8), target));
		}

	}

	void upgrade() {
		upgraded = true;
		attSpeed = 0.3f;
		range = 300;

		texture.loadFromFile("assets/tower1Up.png");
		this->sprite.setTexture(texture);
	}


};