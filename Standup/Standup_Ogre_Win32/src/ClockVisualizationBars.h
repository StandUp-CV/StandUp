#ifndef CLOCK_VISUALIZATION_BARS_H
#define CLOCK_VISUALIZATION_BARS_H

#include "stdafx.h"
#include "OgreFrameListener.h"
#include "Clock.h"
#include "OgreSceneNode.h"
#include "ClockVisualisation.h"

class ClockVisualizationBars : public Ogre::FrameListener, public ClockVisualization
{
public:
	ClockVisualizationBars(Ogre::SceneManager* sceneManager, int hourFormat = 1) : 
		ClockVisualization(sceneManager, hourFormat) {
		// set max values
		mHours = 12 * mHourFormat;
		mMinutes = 60;
		mSeconds = 60;
		// creates the clock
		createClock();
	}

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		// counter for slowed clock update (needs only once per second ;)
		static int second=-1;
		// get current time from clock
		const tm& localTime = Clock::getDisplayTime(Clock::getCurrentSecond());
		float dayInterpolationTime = localTime.tm_hour + (localTime.tm_min * 0.01667f);
		// get the current secs, mins and mHours
		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % (12 * mHourFormat); // in right time format (12 vs 24)

		if(mCurrentSeconds!=second) {
			second = mCurrentSeconds;

			float hrsScale = (float) mCurrentHours/(float) mHours;
			float minsScale = (float) mCurrentMinutes/(float) mMinutes;
			float secsScale = (float) mCurrentSeconds/(float) mSeconds;

			mHoursBarsNode->setScale(0.1f, 0.1f, hrsScale);
			mMinutesBarsNode->setScale(0.1f, 0.1f, minsScale);
			mSecondsBarsNode->setScale(0.1f, 0.1f, secsScale);

			mHoursBarsNode->setPosition(0,12,(hrsScale * 50)-50);
			mMinutesBarsNode->setPosition(0,0,(minsScale * 50)-50);
			mSecondsBarsNode->setPosition(0,-12,(secsScale * 50)-50);
		}

		return true;
	}
protected:
	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();
		mClockNode = rootNode->createChildSceneNode("MainBarsClockNode");

		mClockNode->setPosition(0,0,0);
		mClockNode->setScale(0.66f, 0.66f, 0.66f);
		/*mClockNode->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI), 
			Ogre::Vector3(0,1,1)));*/
		/*mClockNode->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * 0.5f), 
		Ogre::Vector3::NEGATIVE_UNIT_Z));*/
		
		mHoursBarsNode = mClockNode->createChildSceneNode("HoursBarsNode");
		mMinutesBarsNode = mClockNode->createChildSceneNode("MinutesBarsNode");
		mSecondsBarsNode = mClockNode->createChildSceneNode("SecondsBarsNode");

		Ogre::String hoursMaterialName = "Standup/Clock/Hours";
		Ogre::String minutesMaterialName = "Standup/Clock/Minutes";
		Ogre::String secondsMaterialName = "Standup/Clock/Seconds";
		Ogre::String backgroundMaterial = "Standup/Clock/Background";

		Ogre::Entity* tempGeometry;

		// Hours
		tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
		tempGeometry->setMaterialName(hoursMaterialName);
		
		mHoursBarsNode->attachObject(tempGeometry);
		mHoursBarsNode->setPosition(0, 12, 0);

		// Minutes
		tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
		tempGeometry->setMaterialName(minutesMaterialName);

		mMinutesBarsNode->attachObject(tempGeometry);
		mMinutesBarsNode->setPosition(0, 0, 0);

		// Seconds
		tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
		tempGeometry->setMaterialName(secondsMaterialName);

		mSecondsBarsNode->attachObject(tempGeometry);
		mSecondsBarsNode->setPosition(0, -12, 0);

		//Background
		Ogre::SceneNode* background;
		// Hours
		background = mClockNode->createChildSceneNode("Background_Hours");

		tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
		tempGeometry->setMaterialName(backgroundMaterial);

		background->attachObject(tempGeometry);
		background->setScale(0.075f, 0.075f, 1.0f);
		background->setPosition(0,12,0);
		// Minutes
		background = mClockNode->createChildSceneNode("Background_Minutes");

		tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
		tempGeometry->setMaterialName(backgroundMaterial);

		background->attachObject(tempGeometry);
		background->setScale(0.075f, 0.075f, 1.0f);
		background->setPosition(0,0,0);
		// Seconds
		background = mClockNode->createChildSceneNode("Background_Seconds");

		tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
		tempGeometry->setMaterialName(backgroundMaterial);

		background->attachObject(tempGeometry);
		background->setScale(0.075f, 0.075f, 1.0f);
		background->setPosition(0,-12,0);
		//mHoursBarsNode->setScale(0.1f, 0.1f, 1.0f);
		//mMinutesBarsNode->setScale(0.1f, 0.1f, 1.0f);
		//mSecondsBarsNode->setScale(0.1f, 0.1f, 1.0f);

		//mHoursBarsNode->setPosition(10,12,0);
		//mMinutesBarsNode->setPosition(10,0,0);
		//mSecondsBarsNode->setPosition(10,-12,0);
	}
private:
	Ogre::SceneNode* mClockNode;
	Ogre::SceneNode* mHoursBarsNode;
	Ogre::SceneNode* mMinutesBarsNode;
	Ogre::SceneNode* mSecondsBarsNode;
};

#endif // !CLOCK_VISUALIZATION_BARS_H
