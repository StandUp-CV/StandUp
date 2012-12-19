


#include "Sound.h"

Sound::Sound()
{
	unsigned int      version;
	FMOD_RESULT       result;

	system=NULL;
	sound[0]=NULL;
	sound[1]=NULL;

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

	reloadSoundFile(PRERUN, "stuka.wav");
	reloadSoundFile(ALARM, "stuka.wav");
}

bool Sound::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	system->update();
	return true;
}

void Sound::reloadSoundFile(SoundEffect which, Ogre::String path) {
	if (sound[which]) sound[which]->release();
	FMOD_RESULT       result;
	result = system->createSound(path.c_str(), FMOD_HARDWARE, 0, &sound[which]);
	if(result!=FMOD_OK) throw new SoundException();
}

Sound::~Sound()
{
	FMOD_RESULT       result;

	if(sound[0]) result = sound[0]->release();
	if(sound[1]) result = sound[1]->release();
	if(system) result = system->close();
	if(system) result = system->release();
}

void Sound::play(SoundEffect which)
{
	FMOD::Channel *ch;
	system->playSound(FMOD_CHANNEL_FREE,sound[which],false,&ch);
}
