
#ifndef SOUND_H
#define SOUND_H


enum SoundEffect { PRERUN, ALARM };

class SoundException : std::exception
{
	char *what () { return "SoundException"; }
};

class Sound : public Ogre::FrameListener
{
private:

	FMOD::System     *system;
	FMOD::Sound      *sound[2];

public:

	Sound();
	~Sound();

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	void reloadSoundFile(SoundEffect which, Ogre::String path);

	void play(SoundEffect which);
};

#endif