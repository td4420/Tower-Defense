#include "stdafx.h"
#include "Animation.h"
#include <iostream>
void Animation::Init()
{
	//Normal Enemy Animation

	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_000.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_001.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_002.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_003.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_005.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_006.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_007.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_008.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_009.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_010.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_011.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_012.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_013.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_014.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_015.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_016.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_017.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_018.tga"));
	normalMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Left/2_enemies_1_walk_019.tga"));
	
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_000.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_001.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_002.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_003.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_005.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_006.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_007.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_008.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_009.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_010.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_011.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_012.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_013.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_014.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_015.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_016.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_017.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_018.tga"));
	normalMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/NormalEnemy/Right/R_enemies_1_walk_019.tga"));

	//Fast Enemy Animation

	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_000.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_001.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_002.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_003.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_004.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_005.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_006.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_007.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_008.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_009.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_010.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_011.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_012.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_013.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_014.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_015.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_016.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_017.tga"));
	fastMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Left/1_enemies_1_run_018.tga"));

	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_000.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_001.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_002.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_003.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_004.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_005.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_006.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_007.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_008.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_009.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_010.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_011.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_012.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_013.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_014.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_015.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_016.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_017.tga"));
	fastMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/FastEnemy/Right/1_enemies_1_run_018.tga"));

	//Tank Enemy Animation

	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_000.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_001.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_002.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_003.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_004.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_005.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_006.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_007.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_008.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_009.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_010.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_011.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_012.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_013.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_014.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_015.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_016.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_017.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_018.tga"));
	tankMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Left/6_enemies_1_walk_019.tga"));

	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_000.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_001.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_002.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_003.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_004.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_005.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_006.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_007.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_008.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_009.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_010.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_011.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_012.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_013.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_014.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_015.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_016.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_017.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_018.tga"));
	tankMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/TankEnemy/Right/6_enemies_1_walk_019.tga"));
}
int Animation::GetAnimationMoveRight(int type)
{
	if (type == 1)
	{
		if (currentTextureRight == normalMoveRight.size() - 1) currentTextureRight = 0;
		else currentTextureRight++;
		return currentTextureRight;
	}
	if (type == 2)
	{
		if (currentTextureRight == fastMoveRight.size() - 1) currentTextureRight = 0;
		else currentTextureRight++;
		return currentTextureRight;
	}
	if (type == 4)
	{
		if (currentTextureRight == tankMoveRight.size() - 1) currentTextureRight = 0;
		else currentTextureRight++;
		return currentTextureRight;
	}
}
int Animation::GetAnimationMoveLeft(int type)
{
	if (type == 1)
	{
		if (currentTextureLeft == normalMoveLeft.size() - 1)  currentTextureLeft = 0;
		else currentTextureLeft++;
		return currentTextureLeft;
	}
	if (type == 2)
	{
		if (currentTextureLeft == fastMoveLeft.size() - 1)  currentTextureLeft = 0;
		else currentTextureLeft++;
		return currentTextureLeft;
	}
	if (type == 4)
	{
		if (currentTextureLeft == tankMoveLeft.size() - 1)  currentTextureLeft = 0;
		else currentTextureLeft++;
		return currentTextureLeft;
	}
}