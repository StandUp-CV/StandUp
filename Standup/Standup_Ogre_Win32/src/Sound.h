
/// \file src\Sound.h
///
/// \brief Declares the Sound class.

#ifndef SOUND_H
#define SOUND_H

/// \enum SoundEffect
///
/// \brief enumarates sound effects that can be played.

enum SoundEffect { PRERUN, ALARM };

/// \class SoundException
///
/// \brief Exception for signalling sound errors.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class SoundException : std::exception
{
	char *what () { return "SoundException"; }
};

/// \class Sound
///
/// \brief integrates the FMOD library to play the alarm sound effects.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class Sound : public Ogre::FrameListener
{
private:

	FMOD::System     *system;   /*!< The system */
	FMOD::Sound      *sound[2]; /*!< The sound[ 2] */

public:

	/// \fn Sound::Sound();
	///
	/// \brief create FMOD and load sound effects.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	Sound();

	/// \fn Sound::~Sound();
	///
	/// \brief destroy everything.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	~Sound();

	// update event
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/// \fn void Sound::reloadSoundFile(SoundEffect which, Ogre::String path);
	///
	/// \brief load or reload a sound file.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param which
	/// Which sound effect to load
	/// \param path
	/// Full pathname of the file.

	void reloadSoundFile(SoundEffect which, Ogre::String path);

	/// \fn void Sound::play(SoundEffect which);
	///
	/// \brief play a sound file.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param which
	/// Which sound effect to play

	void play(SoundEffect which);
};

#endif