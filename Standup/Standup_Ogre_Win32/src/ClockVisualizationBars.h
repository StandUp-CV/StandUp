#ifndef CLOCK_VISUALIZATION_BARS_H
#define CLOCK_VISUALIZATION_BARS_H

#include "stdafx.h"
#include "OgreFrameListener.h"
#include "Clock.h"
#include "OgreSceneNode.h"
#include "ClockVisualisation.h"
#include "StandupApplication.h"

class ClockVisualizationBars : public Ogre::FrameListener, public ClockVisualization
{
public:
	ClockVisualizationBars(Ogre::SceneManager* sceneManager, Ogre::Camera* cam, int hourFormat = 1) : 
		ClockVisualization(sceneManager, hourFormat), mCamera(cam) {
		// set max values
		mHours = 12 * mHourFormat;
		mMinutes = 60;
		mSeconds = 60;
		// creates the clock
		createClock();
		mLight = mSceneMgr->createLight("light1");
		mLight->setType(Ogre::Light::LT_POINT);
		mLight->setDiffuseColour(0.8,0.8,0.8);
		//mLight->setPosition
	}

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		// counter for slowed clock update (needs only once per second ;)
		static int second=-1;
		static Ogre::Vector3& dir = Ogre::Vector3();
		static Ogre::Ray& ray = Ogre::Ray();
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

			mHoursBarsNode->setPosition(0,12,(hrsScale * 50)-49);
			mMinutesBarsNode->setPosition(0,0,(minsScale * 50)-49);
			mSecondsBarsNode->setPosition(0,-12,(secsScale * 50)-49);
		}

		// mouse orientation
		OIS::MouseState state = StandupApplication::getInstance()->getMouse()->getMouseState();
		ray = Ogre::Ray();
		float x = state.X.abs;
		float y = state.Y.abs;
		float relX = x/(float)state.width;//mCamera->getViewport()->getWidth();
		float relY = y/(float)state.height;//mCamera->getViewport()->getHeight();
		relX = (1-relX);
		relY = (1-relY);
		mCamera->getCameraToViewportRay(relX * mCamera->getViewport()->getWidth(),
			relY * mCamera->getViewport()->getHeight(), &ray);
		dir = Ogre::Vector3(ray.getDirection().x, ray.getDirection().y, ray.getDirection().z);
		dir.normalise();
		//dir *= -1;
		//mDebugNode->setOrientation(Ogre::Quaternion( 
		//	&dir));
		mLight->setPosition(ray.getOrigin());
		mClockNode->setOrientation(
			Ogre::Quaternion( 
			&dir));
			/*mClockNode->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * 0), 
			Ogre::Vector3(0,1,1)));*/
		return true;
	}
protected:
	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();
		mClockNode = rootNode->createChildSceneNode("MainBarsClockNode");
		//mDebugNode = rootNode->createChildSceneNode("DebugNode");
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

		// DEBUG
		//tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);

		//mDebugNode->attachObject(tempGeometry);
		//mDebugNode->setScale(0.01,0.3,0.01);
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
	Ogre::SceneNode* mDebugNode;
	// references the ogre basic camera
	Ogre::Camera* mCamera;
	Ogre::Light* mLight;
};

#endif // !CLOCK_VISUALIZATION_BARS_H
