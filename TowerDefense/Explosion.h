#pragma once
#include "GameObject.h"
#include "SpriteSheet.h"

class Explosion : public GameObject{

	SpriteSheet* sheet;
public:

	Explosion(Vector2f pos)
		:GameObject(pos)
	{

		sheet = new SpriteSheet("assets/explo1.png", 10, 0.05f,false);
		sprite = sheet->getSprite();

	}

	void update()
	{
		sheet->play();
		sprite = sheet->getSprite();
		if (sheet->getCurrentFrame() >= 8) {
			destroyFlag = true;
		}
	}
};