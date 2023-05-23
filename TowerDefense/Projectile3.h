#pragma once
#include "Projectile.h"
#include "SpriteSheet.h"

class Projectile3 : public Projectile
{
	SpriteSheet* sheet;
	Vector2f vel;

public:

	Projectile3(Vector2f pos, Vector2f dir)
		:Projectile(pos)
	{
		deathTime = 5.0f;
		countDeadTime = 0;

		this->speed = 10.3f;

		sheet = new SpriteSheet("assets/pro3.png", 6, 0.05f);
		sprite = sheet->getSprite();
		
		vel = Vector2f(dir.x * speed, dir.y * speed);
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