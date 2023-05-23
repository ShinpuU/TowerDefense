#pragma once
#include "Projectile.h"

class Tower : public GameObject
{
	CircleShape circle;

protected:

	int range;
	float attSpeed;
	float countAttTime = 0;

public:
	bool upgraded = false;

	Tower(Vector2f pos)
		:GameObject(pos)
	{
		
	}
	Tower(Vector2f pos, string textureStr) 
		:GameObject(pos,textureStr,GameObject::TOWER)
	{

		
		
	}
	
	void update()
	{
		
	}

	void draw() {
		GameObject::draw();
		Vector2i mousePos = sf::Mouse::getPosition(*Utils::get().window);
		if (getRect().contains(Vector2f(mousePos.x, mousePos.y))) {
			float radius = range / 2;
			circle.setPosition(Vector2f(getCenter().x - radius, getCenter().y - radius));
			circle.setOutlineThickness(1);
			circle.setRadius(radius);
			circle.setFillColor(Color(0, 0, 0, 0));
			Utils::get().window->draw(circle);

		}

	}


	virtual void setTarget(GameObject* target)
    {

    }

	virtual void attack(vector<Projectile*>* projectiles)
    {
    }
	virtual void upgrade() {

	}


};