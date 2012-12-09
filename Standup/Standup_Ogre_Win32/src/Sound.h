
#ifndef SOUND_H
#define SOUND_H

#include <exception>
#include <fmod.hpp>
#include <fmod_errors.h>

class SoundException : std::exception
{
	char *what () { return "SoundException"; }
};

class Sound
{
private:

	FMOD::System     *system;
	FMOD::Sound      *sound;

public:

	Sound()
	{
		unsigned int      version;
		FMOD_RESULT       result;

		system=NULL;
		sound=NULL;

		result = FMOD::System_Create(&system);
		if(result!=FMOD_OK) throw new SoundException();

		result = system->getVersion(&version);
		if(result!=FMOD_OK) throw new SoundException();

		if (version < FMOD_VERSION)
		{
			//printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
			throw new SoundException();
		}

		result = system->init(32, FMOD_INIT_NORMAL, 0);
		if(result!=FMOD_OK) throw new SoundException();

		result = system->createSound("stuka.wav", FMOD_HARDWARE, 0, &sound);
		if(result!=FMOD_OK) throw new SoundException();



	}

	~Sound()
	{
		FMOD_RESULT       result;

		if(sound) result = sound->release();
		if(system) result = system->close();
		if(system) result = system->release();
	}

	void update()
	{
		system->update();
	}

	void play()
	{
		FMOD::Channel *ch;
		//system->playSound(FMOD_CHANNEL_FREE,sound,false,&ch);
	}
};

#endif