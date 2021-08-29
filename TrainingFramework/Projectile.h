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
    //float firingAngle;

    Vector2 towerPos; 
    Enemies* target;

    bool reachedTarget = false;
    //bool moving = false;// so projectile doesnt change course on flight
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
    Projectile(int type, Shaders shaders, Enemies* e);
    ~Projectile();
};