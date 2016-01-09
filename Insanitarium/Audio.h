#pragma once
#include "irrKlang.h"

class Audio
{
public:
	Audio();
	Audio(irrklang::ISoundEngine*);

	bool ifSoundCurrentlyPlayed(const char*);
	void Play2D(const char*, float, bool);
	void Destroy();
	void Stop(char);
	void Resume();
	void SetVolume(float);
	void Play3D(char*, vec3, bool, float);
	void Update3D(float,float,float,float,float,float);
	~Audio();
private:
	irrklang::ISoundEngine* enginename;
};


