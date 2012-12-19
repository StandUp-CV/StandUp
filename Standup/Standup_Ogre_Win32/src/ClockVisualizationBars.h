/// \file src\ClockVisualizationBars.h
///
/// \brief Declares the clock visualization bars class.

#ifndef CLOCK_VISUALIZATION_BARS_H

/// \def CLOCK_VISUALIZATION_BARS_H
///
/// \brief A macro that defines clock visualization bars h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define CLOCK_VISUALIZATION_BARS_H

#include "ClockVisualisation.h"

/// \class ClockVisualizationBars
///
/// \brief Clock visualization bars.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class ClockVisualizationBars : public Ogre::FrameListener, public ClockVisualization
{
public:

	/// \fn ClockVisualizationBars::ClockVisualizationBars(Ogre::SceneManager* sceneManager,
	/// Ogre::Camera* cam, int hourFormat = 1);
	///
	/// \brief Constructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] sceneManager
	/// If non-null, manager for scene.
	/// \param [in,out] cam
	/// If non-null, the camera.
	/// \param hourFormat
	/// (optional) the hour format.

	ClockVisualizationBars(Ogre::SceneManager* sceneManager, Ogre::Camera* cam, int hourFormat = 1);

	/// \fn bool ClockVisualizationBars::frameRenderingQueued(const Ogre::FrameEvent& evt);
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

protected:

	/// \fn void ClockVisualizationBars::createClock();
	///
	/// \brief Creates the clock.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void createClock();

private:
	Ogre::SceneNode* mClockNode;	/*!< The clock node */
	Ogre::SceneNode* mHoursBarsNode;	/*!< The hours bars node */
	Ogre::SceneNode* mMinutesBarsNode;  /*!< The minutes bars node */
	Ogre::SceneNode* mSecondsBarsNode;  /*!< The seconds bars node */
	Ogre::SceneNode* mDebugNode;	/*!< The debug node */

	// references the ogre basic camera
	Ogre::Camera* mCamera;  /*!< The camera */
	Ogre::Light* mLight;	/*!< The light */

};

#endif // !CLOCK_VISUALIZATION_BARS_H
