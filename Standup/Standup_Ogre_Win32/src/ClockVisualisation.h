////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file src\ClockVisualisation.h
///
/// \brief Declares the clock visualisation base class.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLOCK_VISUALISATION_H

#define CLOCK_VISUALISATION_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class ClockVisualization
///
/// \brief Clock visualization base class for diffrent visualizations of a clock.
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
	/// \brief Constructor of the visualization.
	///
	///	Takes a SceneManager from Ogre to hang nodes into the scenegraph. 
	///	The viualization can handle 12 and 24 hour format.
	///	
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in] sceneManager
	/// If non-null, manager for scene. Gets access to the scene graphs main root node.
	/// \param hourFormat
	/// (optional) the hour format where 1 is 12h format and 2 is 24h format.
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

