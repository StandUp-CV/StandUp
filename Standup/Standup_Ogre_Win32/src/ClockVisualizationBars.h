/// \file src\ClockVisualizationBars.h
///
/// \brief Declares the clock visualization bars class.

#ifndef CLOCK_VISUALIZATION_BARS_H

#define CLOCK_VISUALIZATION_BARS_H

#include "ClockVisualisation.h"

/// \class ClockVisualizationBars
///
/// \brief The class ClockVisualizationBars displays a clock via three bars for hours, minutes and seconds.
///
///	The visualization displays three bars for each hours, minutes and seconds. The visualization itself 
/// rotates to the camera. The scene also contains a light that orients itself to the mouse position in 3D.
///
/// \sa ClockVisualisation, Ogre::FrameListener
/// \author Hans Ferchland
/// \date 19.12.2012

class ClockVisualizationBars : public Ogre::FrameListener, public ClockVisualization
{
public:

	/// \fn ClockVisualizationBars::ClockVisualizationBars(Ogre::SceneManager* sceneManager,
	/// Ogre::Camera* cam, int hourFormat = 1);
	///
	/// \brief Constructor of the bars visualization.
	///	
	///	Takes a SceneManager from Ogre to hang nodes into the scenegraph and a camera that 
	/// will be used to orient the clock visualization to it.
	///	The viualization can handle 12 and 24 hour format.
	///	
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] sceneManager
	/// If non-null, manager for scene. Gets access to the scene graphs main root node.
	/// \param [in,out] cam
	/// If non-null, the camera that will view the scene.
	/// \param hourFormat
	/// (optional) the hour format where 1 is 12h format and 2 is 24h format.
	///	\sa Ogre::SceneManager, Ogre::Camera

	ClockVisualizationBars(Ogre::SceneManager* sceneManager, Ogre::Camera* cam, int hourFormat = 1);

	/// \fn bool ClockVisualizationBars::frameRenderingQueued(const Ogre::FrameEvent& evt);
	///
	/// \brief Frame rendering for updateing from Ogre3D via FrameListener interface.
	///
	///	Updates the clock every second. Updates the camera and animation of the clock.
	///	
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param evt
	/// The frame event from Ogre3D.
	///
	/// \return true if rendering should continue, false otherwise.
	///	\sa Ogre::FrameEvent

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:

	/// \fn void ClockVisualizationBars::createClock();
	///
	/// \brief Creates the bar clock visualization with all components.
	///	
	///	Creates the nodes and hangs them into scenegraph. Creates materials and 
	/// geometry and attaches them to the nodes.
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
