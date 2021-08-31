#pragma once
#include "SFML/Audio.hpp"
#include <vector>
#include <string.h>
#include "Sound.h"


class SoundController {
public:
	static SoundController* s_Instance;
	std::vector<Sound> m_SoundList;
	std::vector<sf::SoundBuffer> m_SoundBuffers;
	std::vector<std::string> m_Music;
	std::vector<sf::Sound> m_Sound;
	sf::Sound placeTowerS;
	sf::Sound sellTowerS;
	sf::Sound Tower1Shoot;
	sf::Sound Tower2Shoot;
	sf::Sound Tower3Shoot;
	sf::Sound upgradeTowerS;

	void BufferTowerSound();
	void Init();
	SoundController();
	~SoundController();

	void GenerateSoundEffect();
	void BufferSoundEffect();
	

	static SoundController* GetInstance();
};