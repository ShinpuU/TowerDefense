#pragma once
#include "Utils.h"



class HealthBar {
    int maxHealth;
    Color color;
    float width;

    RectangleShape rect;
public:
    HealthBar(){}

    HealthBar(int health, Color color,float width) {
        this->maxHealth = health;
        this->color = color;
        this->width = width;
    }

    void draw(int health, Vector2f pos) {
        if (health > 0) {
            float maxHpWidth = width;
            float hpWidth = float(maxHpWidth / maxHealth);

            rect.setPosition(pos);
            rect.setSize(Vector2f(maxHpWidth, 4));
            rect.setFillColor(Color::White);

            Utils::get().window->draw(rect);

            float x = pos.x;

            for (int i = 0; i < health; i++) {
                rect.setPosition(Vector2f(x,pos.y));
                rect.setSize(Vector2f(hpWidth, 4));
                rect.setFillColor(color);

                Utils::get().window->draw(rect);

                x += hpWidth;
            }
        }

    }


};

    