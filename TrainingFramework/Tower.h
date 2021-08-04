#pragma once
#include "Object.h"
#include "Enemies.h"
class Tower :
    public Object
{
public:
    Model towerModel = Model("../Resources/model.txt");
    Texture towerTexture = Texture("../Resources/nen.txt");

    int towerType = 0;
    int damage = 0;
    float range = 0.1f;

    std::vector <Enemies> enemiesInRange;
    Enemies currentTarget;
};

