#include "SoundEffect.h"
#include <iostream>

SoundEffect::SoundEffect(const std::string& sfxPath)
	:m_SoundBuffer(nullptr), m_Sound(nullptr)
{
	m_SoundBuffer = new sf::SoundBuffer();
	if (!m_SoundBuffer->loadFromFile(sfxPath))
	{
		std::cout << "Failed to load sfx: " << sfxPath << std::endl;
		return;
	}
	m_Sound = new sf::Sound(*m_SoundBuffer);
}

SoundEffect::~SoundEffect()
{
	delete m_SoundBuffer;
	delete m_Sound;
}

void SoundEffect::Play()
{
	m_Sound->play();
}
