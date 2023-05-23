
#pragma once


#include "Screen.h"
#include "Button.h"
#include "Game.h"
#include "MSound.h"


class MainMenu : public Screen
{
	World* world;
	vector<GameObject*> gameObjects;
	vector<Button*> buttons;
	bool showHighScore = false;

	vector<int> scores;
public:

	MainMenu() {
		world = new World(&gameObjects);

		buttons.push_back(new Button(0, Vector2f(700, 200), "assets/btn.png", "Play", Vector2f(105, 22), 24));
		buttons.push_back(new Button(1, Vector2f(700, 300), "assets/btn.png", "HighScore", Vector2f(72, 22), 24));
		buttons.push_back(new Button(2, Vector2f(700, 400), "assets/btn.png", "Quit", Vector2f(105, 22), 24));

		MSound::get().playMusic();
	}

	void update() {
		for (Button* button : buttons) {
			button->update();
			if (!button->clicked) {
				continue;
			}

			switch (button->id)
			{
			case 0:
				Utils::get().currentGame = new Game();
				break;
			case 1:
				showHighScore = true;
				scores = Utils::get().readScores();
				sort(scores.begin(), scores.end(), greater<int>());
				break;
			case 2:
				exit(1);
				break;
			}
		}
	}

	void onMouseDown(Event e) {

	}

	void onKeyDown(Event e) {

	}

	void draw() {
		world->draw();
		for (GameObject* obj : gameObjects) {
			obj->draw();
		}



		if (showHighScore) {
			Utils::get().showText("Top 10 scores!", 1050, 200, 24, Color::Black);
			
			int y = 240;

			for (int i = 0; i < 10 && i < scores.size(); i++) {
				Utils::get().showText(to_string(scores[i]), 1090, y, 18, Color::Black);
				y += 30;
			}


		}
		


		Utils::get().showText("K&M Tower defense!", 100, 300, 50, Color::Magenta);
		Utils::get().showText("Press right mouse button to place a turret\n Click on turret and then on arrow to upgrade it", 100, 500, 50, Color::Black);
		for (Button* b : buttons) {
			b->draw();
		}
	}




};

