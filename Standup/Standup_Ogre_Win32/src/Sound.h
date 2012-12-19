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
/// \brief enumarate sound effects that can be played.

enum SoundEffect { PRERUN, ALARM };

/// \class SoundException
///
/// \brief Exception for signalling sound errors.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class SoundException : std::exception
{
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

	// update event
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/// \fn void Sound::reloadSoundFile(SoundEffect which, Ogre::String path);
	///
	/// \brief load or reload a sound file.
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
	/// \brief play a sound file.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param which
	/// The which.

	void play(SoundEffect which);
};

#endif