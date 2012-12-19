
#ifndef CLOCK_VISUALISATION_H
#define CLOCK_VISUALISATION_H

class ClockVisualization
{
public:
	ClockVisualization(Ogre::SceneManager* sceneManager, int hourFormat = 1) 
		: mSceneMgr(sceneManager), mHourFormat(hourFormat) {}
protected:
	// references the clock used for the visualization
	Ogre::SceneManager* mSceneMgr;
	// saves the static values for max hours, mins and secs
	int mHours;
	int mMinutes;
	int mSeconds;
	// saves the current time and gmt offset
	int mCurrentSeconds;
	int mCurrentMinutes;
	int mCurrentHours;
	int mHourFormat;
};

#endif // !CLOCK_VISUALISATION_H

