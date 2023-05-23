#pragma once
#include "Enemy1.h"
#include "Enemy2.h"


class WaveSpawner
{
    int wave;

    float countSpawnTime = 0;
    float spawnTime = 0;
    int maxEnemyCount = 0;
    int enemyCount;
public:

    WaveSpawner(){}

    WaveSpawner(int wave)
    {
        this->wave = wave;

        enemyCount = 0;
        countSpawnTime = 10;
        switch (wave)
        {
        case 1:
            spawnTime = 1.0f;
            maxEnemyCount = 20;
            break;
        case 2:
            spawnTime = 0.8f;
            maxEnemyCount = 30;
            break;
        case 3:
            spawnTime = 0.3f;
            maxEnemyCount = 100;
            break;
        case 4:
            spawnTime = 0.2f;
            maxEnemyCount = 120;
            break;
        case 5:
            spawnTime = 0.1f;
            maxEnemyCount = 200;
            break;
        case 6:
            spawnTime = 0.1f;
            maxEnemyCount = 500;
            break;
        }

    }

    Enemy* spawn()
    {
        countSpawnTime += Utils::get().deltaTime;
        if (countSpawnTime >= spawnTime && enemyCount < maxEnemyCount)
        {
            countSpawnTime = 0;
            enemyCount++;

            Enemy* enemy = nullptr;

            if (rand() % 10 > 3) {
                enemy = new Enemy1(Vector2f(-1 * 16, -1 * 16), Utils::get().path);
            }
            else {
                enemy = new Enemy2(Vector2f(-1 * 16, -1 * 16), Utils::get().path);
            }


            return enemy;
        }
        return nullptr;
    }

    bool isDone()
    {
        return enemyCount >= maxEnemyCount;
    }

};