#pragma once
#include "Projectile.h"
#include "SpriteSheet.h"

class Projectile2 : public Projectile
{
	SpriteSheet* sheet;
	Vector2f vel;

public:

	Projectile2(Vector2f pos, GameObject* target)
		:Projectile(pos)
	{
		deathTime = 5.0f;
		countDeadTime = 0;

		this->speed = 2.3f;
		this->target = target;

		sheet = new SpriteSheet("assets/pro2.png", 6, 0.05f);
		sprite = sheet->getSprite();

		float disc = Utils::get().distance(pos.x, pos.y, target->getCenter().x, target->getCenter().y);
		float normalizedX = (target->getCenter().x - pos.x) / disc;
		float normalizedY = (target->getCenter().y - pos.y) / disc;

		vel = Vector2f(normalizedX * speed, normalizedY * speed);
	}

	void update()
	{
		Projectile::update();
		pos += vel;

		sheet->play();
		sprite = sheet->getSprite();
	}
	void draw() {
		Projectile::draw();
	}


};