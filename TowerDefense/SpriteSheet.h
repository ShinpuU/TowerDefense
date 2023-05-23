#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class SpriteSheet {

    string id;
    Vector2i size;
    Texture texture;
    Sprite sprite;

    float playTime = 0;
    float delayTime = 0;
    int currentFrame = 0;
    int maxFrame = 0;

    bool loop = false;
public:

    SpriteSheet(){}
    SpriteSheet(string filePath, int maxFrame, float delayTime = 0.1f, bool loop = true) {

        this->loop = loop;
        this->maxFrame = maxFrame;
        this->delayTime = delayTime;
        this->playTime = delayTime;
        if (!(texture.loadFromFile(filePath)))
        {
            cout << "Could Not Load File.." << endl;
        }

        this->size = Vector2i(texture.getSize().x / maxFrame,texture.getSize().y);


        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    }

    void play() {

        float deltaTime = Utils::get().deltaTime;

        if (currentFrame >= maxFrame) {
            return;
        }

        this->playTime -= deltaTime;
        if (playTime <= 0) {
            this->playTime = this->delayTime;
            currentFrame++;
            if (currentFrame >= maxFrame && loop) {
                currentFrame = 0;
            }
        }

        sprite.setTextureRect(sf::IntRect(currentFrame * size.x, 0, size.x, size.y));
    }

    int getCurrentFrame() {
        return currentFrame;
    }
    void setCurrentFrame(int f) {
        currentFrame = f;
    }

    Sprite getSprite() {
        return sprite;
    }

    void replay() {
        currentFrame = 0;
    }
    bool isEnd() {
        return currentFrame >= maxFrame;
    }

    void setPosition(Vector2f pos) {
        sprite.setPosition(pos);
    }

    void setScale(Vector2f scale) {
        sprite.setScale(scale);
    }
    Vector2i getSize() {
        return size;
    }

    //void draw() {
    //    window->draw(sprite);
    //}

};