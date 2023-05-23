#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Screen.h"
#include <fstream>
using namespace sf;
using namespace std;

class Utils // singleton global class
{
    sf::Clock deltaClock;
public:
    sf::RenderWindow* window;
    Font* font;

    float deltaTime;
    bool gameOver = false;
    vector<Node*> path;
    Screen* currentGame;

    void init() {

        srand(time(NULL));
        window->setFramerateLimit(60);
        font = new sf::Font();
        if (!font->loadFromFile("assets/font.ttf"))
        {
            printf("error\n");
        }
    }

    void tickClock() { // calculate delta time
        sf::Time dt = deltaClock.restart();
        deltaTime = dt.asSeconds();
    }

    void showText(string str, int x, int y, int size, Color color = { 233,233,233 }) {
        sf::Text text;
        text.setFont(*font);
        text.setFillColor(color);
        text.setCharacterSize(size);
        text.setString(str);
        text.setPosition(Vector2f(x, y));
        window->draw(text);
    }

    void saveScore(int score) {
        std::ofstream outfile;

        outfile.open("score.txt", std::ios_base::app); 
        outfile << score << "\n";
        outfile.close();
    }
    vector<int> readScores() {
        vector<int>scores;
        std::ifstream file("score.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                
                scores.push_back(atoi(line.c_str()));
            }
            file.close();
        }
        return scores;
    }

    float distance(float x1, float y1, float x2, float y2) {
        return sqrt(pow(x2 - x1, 2) +
            pow(y2 - y1, 2) * 1.0);
    }

    static float randomFloat(float a, float b) {
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }

    static int randomInt(int a, int b) {
        return a + (std::rand() % (b - a + 1));
    }

    static Utils& get() {
        static Utils INSTANCE;
        return INSTANCE;
    }
};


