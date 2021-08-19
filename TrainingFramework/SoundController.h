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
	std::vector<sf::Sound> m_Sound;

	void Init();
	SoundController();
	~SoundController();

	void GenerateSoundEffect();
	void BufferSoundEffect();
	//void PlaySoundEffect(std::string soundname, float volume, float pitch, bool loop);

	static SoundController* GetInstance();
};