////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file src\ClockVisualisation.h
///
/// \brief Declares the clock visualisation class.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLOCK_VISUALISATION_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \def CLOCK_VISUALISATION_H
///
/// \brief A macro that defines clock visualisation h.
///
/// \author Hans Ferchland
/// \date 19.12.2012
////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLOCK_VISUALISATION_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class ClockVisualization
///
/// \brief Clock visualization.
///
/// \author Hans Ferchland
/// \date 19.12.2012
////////////////////////////////////////////////////////////////////////////////////////////////////

class ClockVisualization
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn ClockVisualization::ClockVisualization(Ogre::SceneManager* sceneManager,
	/// int hourFormat = 1)
	///
	/// \brief Constructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] sceneManager
	/// If non-null, manager for scene.
	/// \param hourFormat
	/// (optional) the hour format.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	ClockVisualization(Ogre::SceneManager* sceneManager, int hourFormat = 1) 
		: mSceneMgr(sceneManager), mHourFormat(hourFormat) {}
protected:
	Ogre::SceneManager* mSceneMgr;  /*!< Manager for the scene */
	// saves the static values for max hours, mins and secs
	int mHours; /*!< The maximum hours */
	int mMinutes;   /*!< The maximum minutes */
	int mSeconds;   /*!< The maximum seconds */
	// saves the current time and gmt offset
	int mCurrentSeconds;	/*!< The current seconds */
	int mCurrentMinutes;	/*!< The current minutes */
	int mCurrentHours;  /*!< The current hours */
	int mHourFormat;	/*!< The hour format */
};

#endif // !CLOCK_VISUALISATION_H

