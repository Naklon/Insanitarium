#include "stdafx.h"

Audio::Audio()
{
}

Audio::Audio(irrklang::ISoundEngine* engine)
{
	enginename = engine;
	enginename = irrklang::createIrrKlangDevice();
}

bool Audio::ifSoundCurrentlyPlayed(const char *filename)
{
	return this->enginename->isCurrentlyPlaying(filename);
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

void Audio::Play3D(char *name,vec3 position, bool loop,float volume)
{
	irrklang::vec3df newPosition(position.x, position.y, position.z);
	this->enginename->setSoundVolume(volume);
	this->enginename->play3D(name, newPosition, loop, false, false,irrklang::ESM_AUTO_DETECT, true);
}

void Audio::Update3D(float playerX,float playerY,float playerZ,float eyeX,float eyeY,float eyeZ)
{
	this->enginename->setListenerPosition(irrklang::vec3df(playerX, playerY, playerZ), irrklang::vec3df(eyeX, eyeY, eyeZ), irrklang::vec3df(0, 0, 0), irrklang::vec3df(0, 1, 0));
	this->enginename->update();
}


Audio::~Audio()
{
}
