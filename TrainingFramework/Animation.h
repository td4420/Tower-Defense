#pragma once
#include "../Utilities/utilities.h"
#include "Texture.h"
#include <vector>
using namespace std;
class Animation
{
public:
	int currentTextureRight = 0, currentTextureLeft = 0;
	vector<Texture> normalMoveRight;
	vector<Texture> normalMoveLeft;
	vector<Texture> fastMoveLeft;
	vector<Texture> fastMoveRight;
	vector<Texture> tankMoveLeft;
	vector<Texture> tankMoveRight;
	void Init();
	int GetAnimationMoveRight(int type);
	int GetAnimationMoveLeft(int type);
};