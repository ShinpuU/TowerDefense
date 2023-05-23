#pragma once

#include "World.h"
#include "GameObject.h"
#include "WaveSpawner.h"
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"
#include "Button.h"
#include "Explosion.h"
#include "GameOver.h"
#include "YouWin.h"
#include "MSound.h"

class Game : public Screen
{
	World* world;
	vector<GameObject*> gameObjects;

	WaveSpawner waveSpawner;
	int wave = 1;

	enum GAMESTATE
	{
		playing,
		addBuilding1,
		addBuilding2,
		addBuilding3,
		upgrade
	};

	GAMESTATE gameState = playing;


	///
	Tower1* tower1 = nullptr;
	Tower2* tower2 = nullptr;
	Tower3* tower3 = nullptr;

	Tower* selectedTower = nullptr;

	vector<Button*> buttons;

	int gold = 1300;
	int score = 0;

public:

	Game() {

		world = new World(&gameObjects);
		waveSpawner = WaveSpawner(1);


		buttons.push_back(new Button(0,Vector2f(1070, 5), "assets/tower1Icon.png","49",Vector2f(40,40)));
		buttons.push_back(new Button(1, Vector2f(1135, 5), "assets/tower2Icon.png","66", Vector2f(40, 40)));
		buttons.push_back(new Button(2, Vector2f(1200, 5), "assets/tower3Icon.png","86", Vector2f(40, 40)));

		gameObjects.push_back(new GameObject(Vector2f(980, 10), "assets/crystal.png", GameObject::NONE));

		tower1 = new Tower1(Vector2f(0, 0));
		tower2 = new Tower2(Vector2f(0, 0));
		tower3 = new Tower3(Vector2f(0, 0));
	}

	void update() {
		if (Utils::get().gameOver) {
			Utils::get().saveScore(score);
			Utils::get().currentGame = new GameOver(score);

		}

		Vector2i mousePos = sf::Mouse::getPosition(*Utils::get().window);
		vector<Projectile*>* addedProjectiles = new vector<Projectile*>();

		for (GameObject* obj : gameObjects) {
			obj->update();
			if (obj->type == GameObject::TOWER) {
				((Tower*)obj)->attack(addedProjectiles);
			}

			for (GameObject* otherObj : gameObjects) {
				if (obj == otherObj || otherObj == nullptr) {
					continue;
				}


				if (obj->type == GameObject::TOWER && otherObj->type == GameObject::ENEMY) {
					((Tower*)obj)->setTarget(otherObj);
				}

				if (!obj->destroyFlag && obj->type == GameObject::PROJECTILE && otherObj->type == GameObject::ENEMY) {
					if (obj->isColloide(otherObj)) {
						obj->destroyFlag = true;
						((Enemy*)otherObj)->damage(1);
						if (otherObj->destroyFlag) {
							score += Utils::get().randomInt(1, 3);
							gold += Utils::get().randomInt(1, 3);

							MSound::get().playSound("explosion");
							gameObjects.push_back(new Explosion(Vector2f(otherObj->getCenter().x - 24, otherObj->getCenter().y - 24)));
						}
					}

				}

			}
		}

		for (Projectile* p : *addedProjectiles) {
			gameObjects.push_back(p);
		}

		for (int i = 0; i < gameObjects.size();i++) {
			if (gameObjects[i]->destroyFlag) {
				gameObjects.erase(gameObjects.begin() + i);
			}
		}


		switch (gameState)
		{
			case Game::playing:
				if (gameState == GAMESTATE::playing)
				{
					Enemy* e = waveSpawner.spawn();
					if (e != nullptr)
					{
						gameObjects.push_back(e);
					}
				}
				break;
			case Game::addBuilding1:
				tower1->setPos(Vector2f(mousePos.x - tower1->getRect().width/2, mousePos.y - tower1->getRect().height/2));
				break;
			case Game::addBuilding2:
				tower2->setPos(Vector2f(mousePos.x - tower2->getRect().width / 2, mousePos.y - tower2->getRect().height / 2));
				break;
			case Game::addBuilding3:
				tower3->setPos(Vector2f(mousePos.x - tower3->getRect().width / 2, mousePos.y - tower3->getRect().height / 2));
				break;
		}

		for (Button* button : buttons) {
			button->update();

			if (!button->clicked) {
				continue;
			}

			switch (button->id)
			{
				case 0:
					gameState = addBuilding1;
					break;
				case 1:
					gameState = addBuilding2;
					break;
				case 2:
					gameState = addBuilding3;
					break;
			}
		}


		if (waveSpawner.isDone() && countEnemies() <= 0 && wave < 6)
		{
			wave++;
			//Msound.get().play("nextLevel");

			waveSpawner = WaveSpawner(wave);
		}

		// win
		if (wave == 6 && countEnemies() == 0)
		{
			Utils::get().saveScore(score);
			Utils::get().currentGame = new YouWin(score);
		}
	}

	void onMouseDown(Event e) {
		switch (gameState)
		{
			case Game::addBuilding1:
				if (!canPlaceTower(tower1)) {
					return;
				}
				if (gold < 49) {
					gameState = playing;
					return;
				}
				gold -= 49;

				score += 1;
				gameObjects.push_back(new Tower1(tower1->getPos()));
				gameState = playing;
				break;
			case Game::addBuilding2:
				if (!canPlaceTower(tower2)) {
					return;
				}
				if (gold < 66) {
					gameState = playing;
					return;
				}
				gold -= 66;

				score += 2;
				gameObjects.push_back(new Tower2(tower2->getPos()));
				gameState = playing;
				break;
			case Game::addBuilding3:
				if (!canPlaceTower(tower3)) {
					return;
				}
				if (gold < 86) {
					gameState = playing;
					return;
				}
				gold -= 86;

				score += 3;
				gameObjects.push_back(new Tower3(tower3->getPos()));
				gameState = playing;
				break;
			
		}
		Vector2i mousePos = sf::Mouse::getPosition(*Utils::get().window);


		if (selectedTower != nullptr && buttons.size() == 4) {
			if (buttons[3]->getRect().contains(Vector2f(mousePos.x,mousePos.y))) {
				if (gold < 50) {
					return;
				}
				gold -= 50;
				selectedTower->upgrade();
				score += 2;
			}
		}

		selectedTower = nullptr;
		for (GameObject* obj : gameObjects) {
			if (obj->type == GameObject::TOWER) {
				if (obj->getRect().contains(Vector2f(mousePos.x, mousePos.y))) {
					selectedTower = (Tower*)obj;
				}
			}
		}

		if (selectedTower != nullptr && buttons.size() == 3) {
			if (!selectedTower->upgraded) {
				buttons.push_back(new Button(3, Vector2f(1200, 70), "assets/upIcon.png", "50", Vector2f(40, 40)));
			}
		}
		else if(selectedTower == nullptr && buttons.size() == 4) {
			buttons.pop_back();
		}

	}

	void onKeyDown(Event e) {

	}

	void draw() {
		world->draw();

		for (GameObject* obj : gameObjects) {
			obj->draw();
		}

		for (Button* button : buttons) {
			button->draw();
		}

		switch (gameState)
		{
		case Game::addBuilding1:
			tower1->draw();
			break;
		case Game::addBuilding2:
			tower2->draw();
			break;
		case Game::addBuilding3:
			tower3->draw();
			break;
		}

		if (selectedTower != nullptr) {
			RectangleShape rect;
			rect.setPosition(selectedTower->getPos());
			rect.setSize(Vector2f(selectedTower->getRect().width, selectedTower->getRect().height));
			rect.setOutlineThickness(2);
			rect.setFillColor(Color(0, 0, 0, 0));
			rect.setOutlineColor(Color(255, 0, 0, 255));
			Utils::get().window->draw(rect);
		}

		Utils::get().showText("Wave: " + to_string(wave), 980, 30, 20, Color::Red);
		Utils::get().showText(to_string(gold), 1005, 10, 20, Color::Blue);
	}

	int countEnemies() {
		int count = 0;
		for (GameObject* obj : gameObjects) {
			if (obj->type == GameObject::ENEMY) {
				count++;
			}
		}
		return count;
	}

	bool canPlaceTower(Tower* tower) {
		for (GameObject* obj : gameObjects) {
			if (obj->isColloide(tower)) {
				return false;
			}
		}
		return true;
	}

};