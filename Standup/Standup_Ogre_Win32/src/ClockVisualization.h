#ifndef CLOCK_VISUALIZATION_H
#define CLOCK_VISUALIZATION_H

#include "stdafx.h"
#include <vector>
#include <OgreFrameListener.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreMath.h"
#include "clock.h"
#include "OgreQuaternion.h"

// Class for visualization of a clock
class ClockVisualization : public Ogre::FrameListener
{
public:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------
	ClockVisualization(const Ogre::String &name, Ogre::SceneManager* sceneManager, Clock* clock) 
		: mSceneMgr(sceneManager), mClock(clock) {
		createClock();
		const tm& localTime = mClock->getDisplayTime(mClock->getCurrentSecond());
		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % 12;
		mTime = 0;
		mAmbientLight = mSceneMgr->createLight("ClockAmbientLight");
		mAmbientLight->setType(Ogre::Light::LT_POINT);
		mAmbientLight->setCastShadows(true);
		mAmbientLight->setPosition(10, 0, 0);
		//mAmbientLight->setDiffuseColour(Ogre::ColourValue(1,1,1,1));
	}

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		const tm& localTime = mClock->getDisplayTime(mClock->getCurrentSecond());
		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % 12;

		// Light Color interpolate
		Ogre::ColourValue newColor = interpolateColors(localTime.tm_hour + (localTime.tm_min * 0.01667f));
		mAmbientLight->setDiffuseColour(newColor);
		// Seconds
		for (int i = 0; i < 60; i++) {
			if (i <= mCurrentSeconds) {
				mVectorSecondNodes[i]->setVisible(true);
			} else {
				mVectorSecondNodes[i]->setVisible(false);
			}
		}
		// Minutes
		for (int i = 0; i < 60; i++) {
			if (i < mCurrentMinutes) {
				mVectorMinuteNodes[i]->setVisible(true);
			} else {
				mVectorMinuteNodes[i]->setVisible(false);
			}
		}
		// Hours
		for (int i = 0; i < 12; i++) {
			if (i < mCurrentHours) {
				mVectorHourNodes[i]->setVisible(true);
			} else {
				mVectorHourNodes[i]->setVisible(false);
			}
		}

		// Animate the clock via rotation
		float speed = 0.2f;

		mTime += (evt.timeSinceLastEvent * speed);

		float y = 0.1f * Ogre::Math::Sin((mTime) * Ogre::Math::PI);
		float z = 0.1f * Ogre::Math::Cos((mTime) * Ogre::Math::PI);
		mClockRotationNode->setOrientation(Ogre::Quaternion(1,0,y,z));

		if (mTime > 2) mTime = 0;
		// return
		return true;
	}
private:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------

	Ogre::ColourValue interpolateColors(float time) {
		float time2 = (time * time);
		float r = 0.083f * time2 - 2.33f * time + 15;
		float g = -0.0625f * time2 + 1.625f * time - 9;
		float b = 0.01667f * time2 - 0.33f * time + 1.6f;
		return Ogre::ColourValue(r,g,b,0.5f);
	}

	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();

		mClockNode = rootNode->createChildSceneNode("MainClockNode");
		mClockRotationNode = mClockNode->createChildSceneNode("ClockRotationNode");
		mClockNode->setOrientation(Ogre::Quaternion(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * 0.5f), Ogre::Vector3::NEGATIVE_UNIT_X)));
		mHoursNode = mClockRotationNode->createChildSceneNode("HoursNode");
		mMinutesNode = mClockRotationNode->createChildSceneNode("MinutesNode");
		mSecondsNode = mClockRotationNode->createChildSceneNode("SecondsNode");

		Ogre::SceneNode* tempNode;
		Ogre::Entity* tempGeometry;
		Ogre::String hoursMaterialName = "Standup/Clock/Hours";
		Ogre::String minutesMaterialName = "Standup/Clock/Minutes";
		Ogre::String secondsMaterialName = "Standup/Clock/Seconds";

		int hours = 12;
		int minutes = 60;
		int seconds = 60;
		float scaleHours = 0.05f;
		float scaleMinutes = 0.02f;
		float scaleSeconds = 0.01f;
		float x;
		float y;
		float theta;
		float r_hours = 15;
		float r_minutes = 20;
		float r_seconds = 25;
		char numstr[21]; // enough to hold all numbers up to 64-bits

		for (int i  = 0; i < hours; i++) {
			theta = i/(float)hours * Ogre::Math::PI * 2;
			x = r_hours * Ogre::Math::Cos(theta);
			y = r_hours * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dHourNode", i);

			tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
			tempGeometry->setMaterialName(hoursMaterialName);
			tempGeometry->setCastShadows(true);

			tempNode = mHoursNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x), 
				Ogre::Quaternion(Ogre::Radian(theta), Ogre::Vector3::NEGATIVE_UNIT_X));

			tempNode->scale(scaleHours, scaleHours, scaleHours);
			tempNode->attachObject(tempGeometry);
			//tempNode->setVisible(false);
			mVectorHourNodes.push_back(tempNode);
		}

		for (int i  = 0; i < minutes; i++) {
			theta = i/(float)minutes * Ogre::Math::PI * 2;
			x = r_minutes * Ogre::Math::Cos(theta);
			y = r_minutes * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dMinuteNode", i);

			tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
			tempGeometry->setMaterialName(minutesMaterialName);
			tempGeometry->setCastShadows(true);

			tempNode = mMinutesNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x), 
				Ogre::Quaternion(Ogre::Radian(theta), Ogre::Vector3::NEGATIVE_UNIT_X));

			tempNode->scale(scaleMinutes, scaleMinutes, scaleMinutes);
			tempNode->attachObject(tempGeometry);
			mVectorMinuteNodes.push_back(tempNode);
		}

		for (int i  = 0; i < seconds; i++) {
			theta = i/(float)seconds * Ogre::Math::PI * 2.0f;
			x = r_seconds * Ogre::Math::Cos(theta);
			y = r_seconds * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dSecondNode", i);

			tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
			tempGeometry->setMaterialName(secondsMaterialName);
			tempGeometry->setCastShadows(true);

			tempNode = mSecondsNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x), 
				Ogre::Quaternion(Ogre::Radian(theta), Ogre::Vector3::NEGATIVE_UNIT_X));

			tempNode->scale(scaleSeconds, scaleSeconds, 5*scaleSeconds);
			tempNode->attachObject(tempGeometry);
			mVectorSecondNodes.push_back(tempNode);
		}
		//Ogre::SceneNode* zeroNode = mClockNode->createChildSceneNode("ZeroNode", Ogre::Vector3(0, 20, 0));
		//zeroNode->scale(0.05f, 0.05f, 0.05f);
		//zeroNode->attachObject(sphere);
	}

	//-------------------------------------------------------------------------------------
	//		Variables
	//-------------------------------------------------------------------------------------
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* mClockNode;
	Ogre::SceneNode* mClockRotationNode;
	// Nodes for Symbols
	Ogre::SceneNode* mHoursNode;
	Ogre::SceneNode* mMinutesNode;
	Ogre::SceneNode* mSecondsNode;
	// Light node
	Ogre::Light* mAmbientLight;
	// saves the current time and gmt offset
	int mCurrentSeconds;
	int mCurrentMinutes;
	int mCurrentHours;
	float mTime;
	Ogre::Vector3* mRotating;
	Ogre::Quaternion* mRotatingQuat;

	Clock* mClock;
	std::vector <Ogre::SceneNode*> mVectorHourNodes;
	std::vector <Ogre::SceneNode*> mVectorMinuteNodes;
	std::vector <Ogre::SceneNode*> mVectorSecondNodes;
};

#endif