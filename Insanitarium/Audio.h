#pragma once
#include "irrKlang.h"

class Audio
{
public:
	Audio();
	Audio(irrklang::ISoundEngine*);

	void Play2D(const char*, float, bool);
	void Destroy();
	void Stop(char);
	void Resume();
	void SetVolume(float);
	~Audio();
private:
	irrklang::ISoundEngine* enginename;
};


