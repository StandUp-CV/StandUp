#ifndef CLOCK_VISUALIZATION_CIRCLE_H
#define CLOCK_VISUALIZATION_CIRCLE_H

#include "ClockVisualisation.h"

//-------------------------------------------------------------------------------------
// Class for visualization of a clock
class ClockVisualizationCircle : public Ogre::FrameListener, public ClockVisualization
{
public:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------- 
	// Contructor of the visualization
	ClockVisualizationCircle(Ogre::SceneManager* sceneManager, 
		Ogre::Camera* cam, int hourFormat = 1);

	// Updates the clock continously for each frame.
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:

	Ogre::ColourValue interpolateColors(float time);

	void createClock();

	//-------------------------------------------------------------------------------------
	//		Variables
	//-------------------------------------------------------------------------------------
	Ogre::SceneNode* mClockNode;
	Ogre::SceneNode* mMiddleSphereNode;
	// Nodes for Symbols
	Ogre::SceneNode* mHoursNode;
	Ogre::SceneNode* mMinutesNode;
	Ogre::SceneNode* mSecondsNode;
	// Light node
	Ogre::Light* mDaytimeLight;
	Ogre::Vector3* mLightPosition;
	// time update
	float mAnimationTime;
	// references the ogre basic camera
	Ogre::Camera* mCamera;
	Ogre::Vector3 mCameraPosition;
	// holds all nodes for the nodes with the 
	std::vector <Ogre::Entity*> mVectorHourGeom;
	std::vector <Ogre::Entity*> mVectorMinuteGeom;
	std::vector <Ogre::Entity*> mVectorSecondGeom;
};

#endif