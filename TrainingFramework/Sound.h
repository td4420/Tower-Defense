#pragma once
#include <string>
#include "SFML/Audio.hpp"

class Sound {
public:
	std::string m_SoundPath= "placetower.wav";
	float m_SoundPitch = 1.0f;
	float m_Volume = 90.0f;
	bool m_Loop = false;
	sf::SoundBuffer m_SoundBuffer;

	Sound(std::string sp);
	void SoundBuffer();
	std::string GetSoundPath();
	sf::SoundBuffer GetSoundBuffer();
};