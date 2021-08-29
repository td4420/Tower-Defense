#pragma once
#include "Object.h"
#include "Enemies.h"
#include "Projectile.h"
class Tower :
    public Object
{
public:
    //odel towerModel = Model("../Resources/model.txt");
    //Texture towerTexture = Texture("../Resources/nen.txt");

    Vector2 towerPos;//onscreen position
    int towerType = 0;
    int upgrade = 0;
    int damage = 0;
    float range = 0.1f;
    float reloadTime = 3.0f;
    float reloadSpeed = 0.1f;
    float timeSinceLastShot = reloadTime;
    int cost = 0;
    int shotFired = 0;
    bool canFire = true;

    std::vector <Enemies*> enemiesInRange;
    std::vector <Projectile*> projectileOnScreen;
    Enemies* currentTarget;
    Projectile* bullet;

    void Build(int x, int y);
    void Upgrade();
    void Shoot();
    float CalculateDistanceToEnemies(Enemies* e);
    void AddEnemiesInRange(std::vector <Enemies*> EnemyWave);
    void RemoveEnemiesOutOfRange();
    void SetTarget();
    void Update(vector <Enemies*> enemyWave);
    bool CheckReload();
    void CleanUp();

    Tower();
    Tower(int towerType);
    ~Tower();
};