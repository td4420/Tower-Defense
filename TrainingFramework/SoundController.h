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

	sf::Sound placeTowerS;
	sf::Sound sellTowerS;
	sf::Sound tower1Shoot;
	sf::Sound tower2Shoot;
	sf::Sound tower3Shoot;
	sf::Sound upgradeTowerS;

	void BufferTowerSound();
	void Init();
	SoundController();
	~SoundController();

	void GenerateSoundEffect();
	void BufferSoundEffect();
	

	static SoundController* GetInstance();
};