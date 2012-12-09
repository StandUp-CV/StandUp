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
		mCurrentSeconds = mClock->getCurrentSecond() % 60;
		mCurrentMinutes = (mClock->getCurrentSecond() / 60) % 60;
		mCurrentHours = (mClock->getCurrentSecond() / mClock->HOUR) % 12;
		mGMTOffset = 1;
	}
	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		mCurrentSeconds = mClock->getCurrentSecond() % 60;
		mCurrentMinutes = (mClock->getCurrentSecond() / 60) % 60;
		mCurrentHours = (mClock->getCurrentSecond() / mClock->HOUR) % 12;

		// Seconds
		for (int i  = 0; i < 60; i++) {
			if (i < mCurrentSeconds) {
				mVectorSecondNodes[i]->setVisible(true);
			} else {
				mVectorSecondNodes[i]->setVisible(false);
			}
		}
		// Minutes
		for (int i  = 0; i < 60; i++) {
			if (i < mCurrentMinutes) {
				mVectorMinuteNodes[i]->setVisible(true);
			} else {
				mVectorMinuteNodes[i]->setVisible(false);
			}
		}
		// Hours
		for (int i  = 0; i < 12; i++) {
			if (i < mCurrentHours + mGMTOffset) {
				mVectorHourNodes[i]->setVisible(true);
			} else {
				mVectorHourNodes[i]->setVisible(false);
			}
		}

		//float minutes = mClock->

		return true;
	}
private:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------
	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();

		clockNode = rootNode->createChildSceneNode("MainClockNode");
		clockNode->setOrientation(Ogre::Quaternion(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * 0.5f), Ogre::Vector3::NEGATIVE_UNIT_X)));
		mHoursNode = clockNode->createChildSceneNode("HoursNode");
		mMinutesNode = clockNode->createChildSceneNode("MinutesNode");
		mSecondsNode = clockNode->createChildSceneNode("SecondsNode");

		Ogre::SceneNode* tempNode;
		Ogre::Entity* tempGeometry;
		Ogre::String hoursMaterialName = "Examples/Rockwall";
		Ogre::String minutesMaterialName = "Examples/Chrome";
		int hours = 12;
		int minutes = 60;
		int seconds = 60;
		float scaleHours = 0.05f;
		float scaleMinutes = 0.02f;
		float scaleSeconds = 0.01f;
		float x;
		float y;
		float theta;
		float r_hours = 20;
		float r_minutes = 25;
		float r_seconds = 12;
		char numstr[21]; // enough to hold all numbers up to 64-bits

		for (int i  = 0; i < hours; i++) {
			theta = i/(float)hours * Ogre::Math::PI * 2;
			x = r_hours * Ogre::Math::Cos(theta);
			y = r_hours * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dHourNode", i);

			tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
			tempGeometry->setMaterialName(hoursMaterialName);

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
			tempGeometry->setMaterialName(minutesMaterialName);

			tempNode = mSecondsNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x), 
				Ogre::Quaternion(Ogre::Radian(theta), Ogre::Vector3::NEGATIVE_UNIT_X));

			tempNode->scale(scaleSeconds, scaleSeconds, 5*scaleSeconds);
			tempNode->attachObject(tempGeometry);
			mVectorSecondNodes.push_back(tempNode);
		}
		//Ogre::SceneNode* zeroNode = clockNode->createChildSceneNode("ZeroNode", Ogre::Vector3(0, 20, 0));
		//zeroNode->scale(0.05f, 0.05f, 0.05f);
		//zeroNode->attachObject(sphere);
	}

	//-------------------------------------------------------------------------------------
	//		Variables
	//-------------------------------------------------------------------------------------
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* clockNode;
	Ogre::SceneNode* mHoursNode;
	Ogre::SceneNode* mMinutesNode;
	Ogre::SceneNode* mSecondsNode;

	int mCurrentSeconds;
	int mCurrentMinutes;
	int mCurrentHours;
	int mGMTOffset;

	Clock* mClock;
	std::vector <Ogre::SceneNode*> mVectorHourNodes;
	std::vector <Ogre::SceneNode*> mVectorMinuteNodes;
	std::vector <Ogre::SceneNode*> mVectorSecondNodes;
};

#endif