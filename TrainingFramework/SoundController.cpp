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
	m_SoundList = new std::vector<Sound>;
	m_SoundBuffers = new std::vector<sf::SoundBuffer>;

	m_SoundList->push_back(Sound::Sound(LEVEL_COMPLETE_MUSIC));
	m_SoundList->push_back(Sound::Sound(BOSS_ALARM));
	m_SoundList->push_back(Sound::Sound(LOSE));
	m_SoundList->push_back(Sound::Sound(LOSE2));
	m_SoundList->push_back(Sound::Sound(PLACE_TOWER));
	m_SoundList->push_back(Sound::Sound(UPGRADE_TOWER));
	m_SoundList->push_back(Sound::Sound(SHOOT_TOWER_1));
	m_SoundList->push_back(Sound::Sound(SHOOT_TOWER_2));
	m_SoundList->push_back(Sound::Sound(SHOOT_TOWER_3));
	m_SoundList->push_back(Sound::Sound(SELL_TOWER));


	for (int i = 0; i < SoundController::m_SoundList->size(); i++)
	{
		m_SoundList->at(i).SoundBuffer();//set m_buffer 
	}
	for (int i = 0; i < m_SoundList->size(); i++)
	{
		m_SoundBuffers->push_back(m_SoundList->at(i).GetSoundBuffer());

	}
	//std::cout << m_SoundBuffers.size();
	placeTowerS.setBuffer(m_SoundBuffers->at(4));
	sellTowerS.setBuffer(m_SoundBuffers->at(9));
	tower1Shoot.setBuffer(m_SoundBuffers->at(6));
	tower2Shoot.setBuffer(m_SoundBuffers->at(7));
	tower3Shoot.setBuffer(m_SoundBuffers->at(8));
	upgradeTowerS.setBuffer(m_SoundBuffers->at(5));

	delete m_SoundList;
}
//void SoundController::CleanUp()
//{
//	for (int i = 0; i < SoundController::m_SoundList.size(); i++)
//	{
//		delete &SoundController::m_SoundList.at(i);
//	}
//}

