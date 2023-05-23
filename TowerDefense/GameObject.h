#pragma once
#include "Utils.h"

class GameObject {
protected:

	Vector2f pos;
	Sprite sprite;
	Texture texture;
	float speed;
public:
	enum TYPE {
		ENV,
		NONE,
		ENEMY,
		TOWER,
		PROJECTILE
	};
	TYPE type;
	bool destroyFlag = false;
	bool flipX = false;

	GameObject(Vector2f pos, string textureStr, TYPE type) {
		this->pos = pos;
		texture = Texture();
		texture.loadFromFile(textureStr);
		this->sprite.setTexture(texture);
		this->type = type;
	}

	GameObject(Vector2f pos) {
		this->pos = pos;
	}


	virtual void update() {

	}

	virtual void draw() {

		if (flipX) {
			sprite.setScale(Vector2f(-1, 1));
			sprite.setPosition(Vector2f(pos.x + getRect().width, pos.y));
		}
		else {
			sprite.setScale(Vector2f(1, 1));
			sprite.setPosition(pos);
		}

		
		Utils::get().window->draw(sprite);
	}

	bool moveTo(int toX, int toY)
	{
		float disc = Utils::get().distance(pos.x, pos.y, toX, toY);

		float normalizedX = (toX - pos.x) / disc;
		float normalizedY = (toY - pos.y) / disc;

		pos.x += normalizedX * speed;
		pos.y += normalizedY * speed;
		return true;
	}

	virtual FloatRect getRect() {
		return FloatRect(pos.x, pos.y, sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y);
	}

	bool isColloide(GameObject* other) {
		if (other == nullptr) {
			return false;
		}
		FloatRect rect = getRect();
		FloatRect otherRect = other->getRect();
		bool r = rect.intersects(otherRect);
		return r;
	}

	virtual void onCollide(GameObject* other) {

	}


	Vector2f getPos() {
		return pos;
	}

	void setPos(Vector2f p) {
		pos = p;
	}

	//Vector2f getCenter() {
	//	Vector2f center = Vector2f(pos.x + getRect().width / 2, pos.y + getRect().height / 2);
	//	return center;
	//}


	Vector2f getCenter() {
		float x = getRect().left + getRect().width / 2;
		float y = getRect().top + getRect().height / 2;
		return Vector2f(x, y);
	}

};