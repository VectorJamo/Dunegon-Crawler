#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Music
{
private:
	sf::Music* m_Music;

public:
	Music(const std::string& musicPath);
	~Music();

	void Play();
	void Pause();
	void Stop();

	// Ranges from 0 (Mute) -> 100 (Full Volume). Default value is 100.
	void SetVolume(int32_t volume);
	void SetLooping(bool shouldLoop);
};

