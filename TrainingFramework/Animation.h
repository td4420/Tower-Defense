#pragma once
#include "../Utilities/utilities.h"
#include "Texture.h"
#include <vector>
using namespace std;
class Animation
{
public:
	int currentTextureRight = 0 , currentTextureLeft = 0;
	vector<Texture> animationMoveRight;
	vector<Texture> animationMoveLeft;
	void InitEnemies();
	int GetAnimationMoveRight();
	int GetAnimationMoveLeft();
};