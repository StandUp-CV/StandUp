/// \file src\ClockVisualizationCircle.h
///
/// \brief Declares the clock visualization circle class.

#ifndef CLOCK_VISUALIZATION_CIRCLE_H

/// \def CLOCK_VISUALIZATION_CIRCLE_H
///
/// \brief A macro that defines clock visualization circle h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define CLOCK_VISUALIZATION_CIRCLE_H

#include "ClockVisualisation.h"

/// \class ClockVisualizationCircle
///
/// \brief Class for visualization of a clock.
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
	/// \brief Contructor of the visualization.
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

	ClockVisualizationCircle(Ogre::SceneManager* sceneManager, 
		Ogre::Camera* cam, int hourFormat = 1);

	/// \fn bool ClockVisualizationCircle::frameRenderingQueued(const Ogre::FrameEvent& evt);
	///
	/// \brief Updates the clock continously for each frame.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param evt
	/// The event.
	///
	/// \return true if it succeeds, false if it fails.

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:

	/// \fn Ogre::ColourValue ClockVisualizationCircle::interpolateColors(float time);
	///
	/// \brief Interpolate colors.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param time
	/// The time.
	///
	/// \return .

	Ogre::ColourValue interpolateColors(float time);

	/// \fn void ClockVisualizationCircle::createClock();
	///
	/// \brief Creates the clock.
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
	/// \brief holds all nodes for the nodes with the.
	///
	/// \return The m vector hour geometry.

	std::vector <Ogre::Entity*> mVectorHourGeom;

	/// \property std::vector <Ogre::Entity*> mVectorMinuteGeom
	///
	/// \brief Gets the vector minute geometry.
	///
	/// \return The m vector minute geometry.

	std::vector <Ogre::Entity*> mVectorMinuteGeom;

	/// \property std::vector <Ogre::Entity*> mVectorSecondGeom
	///
	/// \brief Gets the vector second geometry.
	///
	/// \return The m vector second geometry.

	std::vector <Ogre::Entity*> mVectorSecondGeom;
};

#endif