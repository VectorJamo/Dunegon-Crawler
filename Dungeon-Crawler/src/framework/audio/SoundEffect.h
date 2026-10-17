#pragma once
#include <SFML/Audio.hpp>

class SoundEffect
{
private:
	sf::SoundBuffer* m_SoundBuffer;
	sf::Sound* m_Sound;

public:
	SoundEffect(const std::string& sfxPath);
	~SoundEffect();

	void Play();
};