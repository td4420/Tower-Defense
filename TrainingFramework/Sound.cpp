#pragma once
#include "stdafx.h"
#include "Sound.h"


Sound::Sound(std::string sp)
{
	m_SoundPath = sp;
}

void Sound::SoundBuffer()
{
	if (m_SoundBuffer.loadFromFile(m_SoundPath)) {
		m_SoundBuffer.loadFromFile(m_SoundPath);
		printf("load succcess buffer %s\n", &m_SoundPath);
	}
	if (!m_SoundBuffer.loadFromFile(m_SoundPath)) {
		printf("fail to load buffer %s\n", &m_SoundPath);
	}
}

std::string Sound::GetSoundPath()
{
	return m_SoundPath;
}

sf::SoundBuffer Sound::GetSoundBuffer()
{
	return m_SoundBuffer;
}