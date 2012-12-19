/// \file src\Sound.h
///
/// \brief Declares the sound class.

#ifndef SOUND_H

/// \def SOUND_H
///
/// \brief A macro that defines sound h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define SOUND_H

/// \enum SoundEffect
///
/// \brief Values that represent SoundEffect.

enum SoundEffect { PRERUN, ALARM };

/// \class SoundException
///
/// \brief Exception for signalling sound errors.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class SoundException : std::exception
{
	/// \fn char SoundException::*what ()
	///
	/// \brief Gets the what.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return null if it fails, else.

	char *what () { return "SoundException"; }
};

/// \class Sound
///
/// \brief Sound.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class Sound : public Ogre::FrameListener
{
private:

	FMOD::System     *system;   /*!< The system */
	FMOD::Sound      *sound[2]; /*!< The sound[ 2] */

public:

	/// \fn Sound::Sound();
	///
	/// \brief Default constructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	Sound();

	/// \fn Sound::~Sound();
	///
	/// \brief Destructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	~Sound();

	/// \fn bool Sound::frameRenderingQueued(const Ogre::FrameEvent& evt);
	///
	/// \brief Frame rendering queued.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param evt
	/// The event.
	///
	/// \return true if it succeeds, false if it fails.

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/// \fn void Sound::reloadSoundFile(SoundEffect which, Ogre::String path);
	///
	/// \brief Reload sound file.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param which
	/// The which.
	/// \param path
	/// Full pathname of the file.

	void reloadSoundFile(SoundEffect which, Ogre::String path);

	/// \fn void Sound::play(SoundEffect which);
	///
	/// \brief Plays the given which.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param which
	/// The which.

	void play(SoundEffect which);
};

#endif