#pragma once
#include "Object.h"
#include "Enemies.h"
#include "Projectile.h"
class Tower :
    public Object
{
public:
    Model towerModel = Model("../Resources/model.txt");
    Texture towerTexture = Texture("../Resources/nen.txt");

    Vector2 towerPos;//onscreen position
    int towerType = 0;
    int damage = 0;
    float range = 0.1f;
    int reloadTime = 1000;
    int cost = 0;
    bool canAttack;

    std::vector <Enemies*> enemiesInRange;
    std::vector <Projectile*> projectileOnScreen;
    Enemies currentTarget;

    void Build(int x, int y);
    void Shoot();
    float CalculateDistanceToEnemies(Enemies *e);
    void AddEnemiesInRange(std::vector <Enemies*> EnemyWave);
    void RemoveEnemiesOutOfRange();
    void SetTarget();
    void Update();
    //void 

    Tower();
    Tower(int towerType);
};
