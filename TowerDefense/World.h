#pragma once
#include "Utils.h"
#include <fstream>
#include <vector>
#include "GameObject.h"
#include "PathGenerator.h"


class World {

	int size = 80 * 45;
	sf::Texture texture;

	sf::VertexArray quad;
	int rows = 45;
	int cols = 80;

public:

	World(vector<GameObject*>* gameObjects) {
		srand(time(nullptr));

		texture.loadFromFile("assets/pelouse.png");


		ifstream file("world.txt");
		string line;

		int row = 0;
		int i = 0;
		int x = 0;
		int y = 0;

		int tileSize = 16;
		int** grid = new int* [rows];
		for (int row = 0; row < rows; row++) {
			grid[row] = new int[cols];
			for (int col = 0; col < cols; col++) {
				grid[row][col] = 0;
			}
		}

		quad = sf::VertexArray(sf::Quads, size * 4);

		while (getline(file, line))
		{
			for (int col = 0; col < line.size(); col++) {

				if (line[col] == '3') {
					gameObjects->push_back(new GameObject(Vector2f(x, y), "assets/bush.png", GameObject::ENV));
				}
				else {
					quad[i].position = sf::Vector2f(x, y);
					quad[i + 1].position = sf::Vector2f(x + tileSize, y);
					quad[i + 2].position = sf::Vector2f(x + tileSize, y + tileSize);
					quad[i + 3].position = sf::Vector2f(x, y + tileSize);

					quad[i].texCoords = sf::Vector2f(0.f, 0.f);
					quad[i + 1].texCoords = sf::Vector2f(tileSize, 0.f);
					quad[i + 2].texCoords = sf::Vector2f(tileSize, tileSize);
					quad[i + 3].texCoords = sf::Vector2f(0.f, tileSize);

					i += 4;
				}

				
				x += tileSize;
			}
			row++;
			y += tileSize;
			x = 0;
		}
		file.close();

		PathGenerator pathGenerator = PathGenerator(grid);
		Utils::get().path = pathGenerator.getRandomPath();
		for (Node* n : Utils::get().path) {
			gameObjects->push_back(new GameObject(Vector2f(n->col * 16,n->row * 16), "assets/path.png", GameObject::ENV));
		}

	}

	void update() {


	}

	void draw() {
		Utils::get().window->draw(quad, &texture);
	}


};