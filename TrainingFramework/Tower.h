#pragma once
#include "Object.h"
#include "Enemies.h"
class Tower :
    public Object
{
public:
    Model towerModel = Model("../Resources/model.txt");
    Texture towerTexture = Texture("../Resources/nen.txt");

    Vector2 towerPos;
    int towerType = 0;
    int damage = 0;
    float range = 0.1f;
    int reloadTime = 1000;
    int cost = 0;

    std::vector <Enemies*> enemiesInRange;
    Enemies currentTarget;

    void Build(int x, int y);
    void Shoot();
    float CaculateDistanceToEnemies(Enemies *e);
    void AddEnemiesInRange(std::vector <Enemies*> EnemyWave);
    void RemoveEnemiesOutOfRange();
    void SetTarget();
    //void 

    Tower();
    Tower(int towerType);
};
