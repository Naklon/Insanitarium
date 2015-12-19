#include "stdafx.h"

Audio::Audio()
{
}

Audio::Audio(irrklang::ISoundEngine* engine)
{
	enginename = engine;
	enginename = irrklang::createIrrKlangDevice();
}

void Audio::Play2D(const char* name, float volume, bool ifloop)
{
	this->enginename->setSoundVolume(volume);
	this->enginename->play2D(name, ifloop);
}

void Audio::Destroy()
{
	this->enginename->drop();
}

void Audio::Stop(char action)
{
	if (action == 'S')
		this->enginename->stopAllSounds();
	else if (action == 'P')
		this->enginename->setAllSoundsPaused(true);
}
void Audio::Resume()
{
	this->enginename->setAllSoundsPaused(false);

}

void Audio::SetVolume(float vol)
{
	this->enginename->setSoundVolume(vol);
}


Audio::~Audio()
{
}
