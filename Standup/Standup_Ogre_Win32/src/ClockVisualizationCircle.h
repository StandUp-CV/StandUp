/// \file src\ClockVisualizationCircle.h
///
/// \brief Declares the clock visualization circle class.

#ifndef CLOCK_VISUALIZATION_CIRCLE_H

#define CLOCK_VISUALIZATION_CIRCLE_H

#include "ClockVisualisation.h"

/// \class ClockVisualizationCircle
///
/// \brief The class ClockVisualizationCircle displays a clock via three cirlces of spheres or cubes for hours, minutes and seconds.
///
///	The visualization displays three cirlces for each hours, minutes and seconds. The camera rotates around the clock. 
/// The scene also contains a light that will light the scene according to the daytime.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class ClockVisualizationCircle : public Ogre::FrameListener, public ClockVisualization
{
public:
	// -------------------------------------------------------------------------------------
	// 		Methods
	// -------------------------------------------------------------------------------------

	/// \fn ClockVisualizationCircle::ClockVisualizationCircle(Ogre::SceneManager* sceneManager,
	/// Ogre::Camera* cam, int hourFormat = 1);
	///
	/// \brief Contructor of the circle visualization.
	///	 
	///	Takes a SceneManager from Ogre to hang nodes into the scenegraph and a camera that 
	/// will rotate around the clock.
	///	The viualization can handle 12 and 24 hour format.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in] sceneManager
	/// If non-null, manager for scene.
	/// \param [in] cam
	/// If non-null, the camera that will view the scene and rotate around the clock.
	/// \param hourFormat
	/// (optional) the hour format.
	///	\sa Ogre::SceneManager, Ogre::Camera
	
	ClockVisualizationCircle(Ogre::SceneManager* sceneManager, 
		Ogre::Camera* cam, int hourFormat = 1);

	/// \fn bool ClockVisualizationCircle::frameRenderingQueued(const Ogre::FrameEvent& evt);
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
	///	\sa Oger::FrameEvent

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:

	/// \fn Ogre::ColourValue ClockVisualizationCircle::interpolateColors(float time);
	///
	/// \brief Interpolates the colors for the daytime-light.
	///	 
	///	Uses a color-ramp implemented in colours.h and interpolates between two values for each update.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param time
	/// The current time from 0 to 24.
	///
	/// \return The new color value of the daytime-light.

	Ogre::ColourValue interpolateColors(float time);

	/// \fn void ClockVisualizationCircle::createClock();
	///
	/// \brief Creates the circle clock visualization with all components.
	///	
	///	Creates the nodes and hangs them into scenegraph. Creates materials and 
	/// geometry and attaches them to the nodes.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void createClock();

	// -------------------------------------------------------------------------------------
	// 		Variables
	// -------------------------------------------------------------------------------------. 
	Ogre::SceneNode* mClockNode;	/*!< The clock node */
	Ogre::SceneNode* mMiddleSphereNode; /*!< The middle sphere node */
	// Nodes for Symbols
	Ogre::SceneNode* mHoursNode;	/*!< The hours node */
	Ogre::SceneNode* mMinutesNode;  /*!< The minutes node */
	Ogre::SceneNode* mSecondsNode;  /*!< The seconds node */
	// Light node
	Ogre::Light* mDaytimeLight; /*!< The daytime light */
	Ogre::Vector3* mLightPosition;  /*!< The light position */
	// time update
	float mAnimationTime;   /*!< Time of the animation */
	// references the ogre basic camera
	Ogre::Camera* mCamera;  /*!< The camera */
	Ogre::Vector3 mCameraPosition;  /*!< The camera position */

	/// \property std::vector <Ogre::Entity*> mVectorHourGeom
	///
	/// \brief holds all nodes for the hours.
	///
	/// \return The vector with the hour geometrys.

	std::vector <Ogre::Entity*> mVectorHourGeom;

	/// \property std::vector <Ogre::Entity*> mVectorMinuteGeom
	///
	/// \brief holds all nodes for the minutes.
	///
	/// \return The vector with the minute geometrys.

	std::vector <Ogre::Entity*> mVectorMinuteGeom;

	/// \property std::vector <Ogre::Entity*> mVectorSecondGeom
	///
	/// \brief holds all nodes for the seconds.
	///
	/// \return The vector with the second geometrys.

	std::vector <Ogre::Entity*> mVectorSecondGeom;
};

#endif