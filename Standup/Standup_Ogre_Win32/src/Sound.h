
#ifndef SOUND_H
#define SOUND_H

// enumarate sound effects that can be played
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

	// update event
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// load or reload a sound file
	void reloadSoundFile(SoundEffect which, Ogre::String path);

	// play a sound file
	void play(SoundEffect which);
};

#endif