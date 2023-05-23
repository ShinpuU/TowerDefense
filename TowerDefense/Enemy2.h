#pragma once
#include "SpriteSheet.h"
#include "Enemy.h"
#include "Node.h"

class Enemy2 : public Enemy
{

	bool onGround = false;
	float timeToflip;

	SpriteSheet* walkSheet;
	SpriteSheet* hitSheet;
	SpriteSheet* currentSheet;
	vector<Node*> path;
	int currentTarget = 0;

public:

	Enemy2(Vector2f pos, vector<Node*> path)
		:Enemy(pos)
	{
		this->type = GameObject::ENEMY;

		walkSheet = new SpriteSheet("assets/enemy2_walk.png", 10, 0.05f);
		hitSheet = new SpriteSheet("assets/enemy2_hit.png", 5, 0.05f);
		currentSheet = walkSheet;

		sprite = currentSheet->getSprite();
		this->path = path;

		health = 8;
		this->speed = 0.7f;

		this->healthbar = HealthBar(health, Color::Red, getRect().width);
	}


	void update()
	{
		if (currentTarget > path.size() - 1)
		{
			Utils::get().gameOver = true;
			return;
		}

		Vector2f target = Vector2f(path[currentTarget]->col * 16, path[currentTarget]->row * 16);
		moveTo(target.x, target.y);
		if (Utils::get().distance(pos.x, pos.y, target.x, target.y) < 5)
		{
			currentTarget++;
		}

		if (target.x > pos.x)
		{
			flipX = false;
		}
		else if (target.x < pos.x)
		{
			flipX = true;
		}

		if (currentSheet == hitSheet && currentSheet->getCurrentFrame() == 4)
		{
			currentSheet = walkSheet;
		}

		sprite = currentSheet->getSprite();
		currentSheet->play();
	}

	void draw()
	{
		Enemy::draw();
	}

	FloatRect getRect() {
		return FloatRect(pos.x, pos.y, currentSheet->getSize().x, currentSheet->getSize().y);
	}

	void damage(int damage)
	{
		health -= damage;

		currentSheet = hitSheet;
		currentSheet->setCurrentFrame(0);

		if (health <= 0)
		{
			destroyFlag = true;
		}
	}

};