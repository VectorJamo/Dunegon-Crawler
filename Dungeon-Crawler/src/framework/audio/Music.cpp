#include "Music.h"

Music::Music(const std::string& musicPath)
{
	m_Music = new sf::Music();
	if (!m_Music->openFromFile(musicPath))
	{
		std::cout << "Failed to load music: " << musicPath << std::endl;
		return;
	}
}

Music::~Music()
{
	delete m_Music;
}

void Music::Play()
{
	m_Music->play();
}

void Music::Pause()
{
	m_Music->pause();
}

void Music::Stop()
{
	m_Music->stop();
}

void Music::SetVolume(int32_t volume)
{
	m_Music->setVolume((float)volume);
}

void Music::SetLooping(bool shouldLoop)
{
	m_Music->setLooping(shouldLoop);
}
