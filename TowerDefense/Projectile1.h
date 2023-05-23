#pragma once
#include "Projectile.h"
#include "SpriteSheet.h"

class Projectile1 : public Projectile
{
	SpriteSheet* sheet;

public:

	Projectile1(Vector2f pos, GameObject* target)
		:Projectile(pos)
	{
		this->speed = 4.3f;
		this->target = target;

		sheet = new SpriteSheet("assets/pro1.png", 6, 0.05f);
		sprite = sheet->getSprite();

	}

	void update()
	{
		Projectile::update();

		moveTo(target->getCenter().x, target->getCenter().y);

		sheet->play();
		sprite = sheet->getSprite();
	}
	void draw() {
		Projectile::draw();
	}


};