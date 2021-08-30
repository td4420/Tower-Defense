#pragma once
#include "Object.h"
#include "Enemies.h"
#include "Shaders.h"
class Projectile :
    public Object
{
public:
    int projectileType;//same as towerType 
    int damage = 0;
    float movementSpeed = 0.005f;

    Vector2 towerPos; 
    Enemies* target = nullptr;

    bool reachedTarget = false;
    bool nullified = false;

    float CalculateDistanceToTarget();
    void SetFiringLocation(float initX, float initY);//Projectile spawns on tower location
    void CheckReachedTarget();
    void Bounce(vector <Enemies*> enemiesWave);// only for type 4 glaive tower
    float GetAngleToEnemies();
    void Move(float angle);

    void Reset();

    Projectile();
    Projectile(int type);
    Projectile(Projectile* p);
    Projectile(int type, Shaders shaders);//initX, initY is location of the Tower that fires
    ~Projectile();
};