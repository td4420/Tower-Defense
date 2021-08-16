#pragma once
#include"stdafx.h"
#include "SoundController.h"
#include <iostream>
#define LEVEL_COMPLETE_MUSIC "levelcomplete.wav"
#define BOSS_ALARM "bossalarm.wav"
#define LOSE "lose.wav"
#define LOSE2 "lose2.wav"
#define PLACE_TOWER "placetower.wav"
#define UPGRADE_TOWER "upgrade.wav"
#define SHOOT_TOWER "shoot.wav"
SoundController* SoundController::s_Instance = NULL;

SoundController::SoundController() {
	SoundController::GenerateSoundEffect();
	SoundController::BufferSoundEffect();
}

SoundController::~SoundController() {

}
SoundController* SoundController::GetInstance() {
	if (!s_Instance)
		s_Instance = new SoundController();
	return  s_Instance;
}
void Init()
{

}
void SoundController::GenerateSoundEffect()
{
	SoundController::m_SoundList.push_back(Sound::Sound(LEVEL_COMPLETE_MUSIC));
	SoundController::m_SoundList.push_back(Sound::Sound(BOSS_ALARM));
	SoundController::m_SoundList.push_back(Sound::Sound(LOSE));
	SoundController::m_SoundList.push_back(Sound::Sound(LOSE2));
	SoundController::m_SoundList.push_back(Sound::Sound(UPGRADE_TOWER));
	SoundController::m_SoundList.push_back(Sound::Sound(SHOOT_TOWER));
	SoundController::m_SoundList.push_back(Sound::Sound(PLACE_TOWER));
	for (int i = 0; i < SoundController::m_SoundList.size(); i++)
	{
		std::cout << SoundController::m_SoundList.at(i).GetSoundPath() << std::endl;
		printf("%f \n", SoundController::m_SoundList.at(i).m_Volume);
		printf("%d \n", SoundController::m_SoundList.at(i).m_Loop);
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
}
