#pragma once
#include"stdafx.h"
#include "SoundController.h"
#include <iostream>
#define LEVEL_COMPLETE_MUSIC "./Sound/levelcomplete.wav"
#define BOSS_ALARM "./Sound/bossalarm.wav"
#define LOSE "./Sound/lose.wav"
#define LOSE2 "./Sound/lose2.wav"
#define PLACE_TOWER "./Sound/placetower.wav"
#define UPGRADE_TOWER "./Sound/upgrade.wav"
#define SHOOT_TOWER_1 "./Sound/shoot1.wav"
#define SHOOT_TOWER_2 "./Sound/shoot2.wav"
#define SHOOT_TOWER_3 "./Sound/shoot3.wav"
#define SELL_TOWER "./Sound/selltower.wav"


SoundController* SoundController::s_Instance = NULL;

SoundController::SoundController() {
	GenerateSoundEffect();
	BufferSoundEffect();
}

SoundController::~SoundController() {

}
SoundController* SoundController::GetInstance() {
	if (!s_Instance)
		s_Instance = new SoundController();
	return  s_Instance;
}

void SoundController::GenerateSoundEffect()
{
	SoundController::m_SoundList.push_back(Sound::Sound(LEVEL_COMPLETE_MUSIC));
	SoundController::m_SoundList.push_back(Sound::Sound(BOSS_ALARM));
	SoundController::m_SoundList.push_back(Sound::Sound(LOSE));
	SoundController::m_SoundList.push_back(Sound::Sound(LOSE2));
	SoundController::m_SoundList.push_back(Sound::Sound(PLACE_TOWER));
	SoundController::m_SoundList.push_back(Sound::Sound(UPGRADE_TOWER));
	SoundController::m_SoundList.push_back(Sound::Sound(SHOOT_TOWER_1));
	SoundController::m_SoundList.push_back(Sound::Sound(SHOOT_TOWER_2));
	SoundController::m_SoundList.push_back(Sound::Sound(SHOOT_TOWER_3));
	SoundController::m_SoundList.push_back(Sound::Sound(SELL_TOWER));
	
	
	for (int i = 0; i < SoundController::m_SoundList.size(); i++)
	{
		SoundController::m_SoundList.at(i).SoundBuffer();//set m_buffer 
	}
	printf("\n\n");
}

void SoundController::BufferSoundEffect()
{
	for (int i = 0; i < SoundController::m_SoundList.size(); i++)
	{
		SoundController::m_SoundBuffers.push_back(SoundController::m_SoundList.at(i).GetSoundBuffer());
		
	}
	//std::cout << m_SoundBuffers.size();
	placeTowerS.setBuffer(m_SoundBuffers.at(4));
	sellTowerS.setBuffer(m_SoundBuffers.at(9));
	tower1Shoot.setBuffer(m_SoundBuffers.at(6));
	tower2Shoot.setBuffer(m_SoundBuffers.at(7));
	tower3Shoot.setBuffer(m_SoundBuffers.at(8));
	upgradeTowerS.setBuffer(m_SoundBuffers.at(5));
}

//void SoundController::CleanUp()
//{
//	for (int i = 0; i < SoundController::m_SoundList.size(); i++)
//	{
//		delete &SoundController::m_SoundList.at(i);
//	}
//}

