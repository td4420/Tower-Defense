#include "stdafx.h"
#include "Animation.h"
#include <iostream>
void Animation::InitEnemies()
{
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_000.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_001.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_002.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_003.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_005.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_006.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_007.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_008.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_009.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_010.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_011.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_012.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_013.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_014.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_015.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_016.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_017.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_018.tga"));
	animationMoveLeft.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_019.tga"));
	
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_000.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_001.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_002.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_003.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_005.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_006.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_007.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_008.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_009.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_010.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_011.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_012.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_013.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_014.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_015.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_016.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_017.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_018.tga"));
	animationMoveRight.push_back(Texture("../ResourcesPacket/AnimationMove/Right/R_enemies_1_walk_019.tga"));

}
int Animation::GetAnimationMoveRight()
{
	if (currentTextureRight == animationMoveRight.size() - 1) currentTextureRight = 0;
	else currentTextureRight++;
	return currentTextureRight;
}
int Animation::GetAnimationMoveLeft()
{
	if (currentTextureLeft == animationMoveLeft.size() - 1)  currentTextureLeft = 0;
	else currentTextureLeft++;
	return currentTextureLeft;
}