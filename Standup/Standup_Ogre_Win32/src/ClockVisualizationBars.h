
#ifndef CLOCK_VISUALIZATION_BARS_H
#define CLOCK_VISUALIZATION_BARS_H

#include "ClockVisualisation.h"

class ClockVisualizationBars : public Ogre::FrameListener, public ClockVisualization
{
public:
	ClockVisualizationBars(Ogre::SceneManager* sceneManager, Ogre::Camera* cam, int hourFormat = 1);

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	void createClock();

private:
	Ogre::SceneNode* mClockNode;
	Ogre::SceneNode* mHoursBarsNode;
	Ogre::SceneNode* mMinutesBarsNode;
	Ogre::SceneNode* mSecondsBarsNode;	
	Ogre::SceneNode* mDebugNode;

	// references the ogre basic camera
	Ogre::Camera* mCamera;
	Ogre::Light* mLight;

};

#endif // !CLOCK_VISUALIZATION_BARS_H
