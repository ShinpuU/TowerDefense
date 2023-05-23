#pragma once
#include "Game.h"

class Game;


class GameOver : public Screen
{
	vector<Button*> buttons;
	int score;
public:

	GameOver(int score) {
		this->score = score;
		buttons.push_back(new Button(1, Vector2f(700, 300), "assets/btn.png", "Quit",      Vector2f(105, 22), 24));
	}

	void update() {
		for (Button* button : buttons) {
			button->update();
			if (!button->clicked) {
				continue;
			}

			switch (button->id)
			{
			
			case 1:
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
		Utils::get().showText("Game Over!", 300, 300, 42, Color::Red);
		Utils::get().showText("Score:  " + to_string(score), 300, 400, 42, Color::White);
		for (Button* b : buttons) {
			b->draw();
		}
	}




};

