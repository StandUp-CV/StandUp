#ifndef CLOCK_VISUALIZATION_H
#define CLOCK_VISUALIZATION_H

#include "stdafx.h"
#include <vector>
#include <OgreFrameListener.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreMath.h"
#include "clock.h"

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
	}
	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		return true;
	}
private:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------
	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();

		clockNode = rootNode->createChildSceneNode("MainClockNode");
		hoursNode = clockNode->createChildSceneNode("HoursNode");
		minutesNode = clockNode->createChildSceneNode("MinutesNode");

		Ogre::SceneNode* tempNode;
		Ogre::Entity* tempSphere;
		Ogre::String hoursMaterialName = "Examples/Rockwall";
		Ogre::String minutesMaterialName = "Examples/Chrome";
		int hours = 12;
		int minutes = 60;
		float scaleHours = 0.05f;
		float scaleMinutes = 0.01f;
		float x;
		float y;
		float theta;
		float r_hours = 20;
		float r_minutes = 25;
		char numstr[21]; // enough to hold all numbers up to 64-bits

		for (int i  = 0; i < hours; i++) {
			theta = i/(float)hours * Ogre::Math::PI * 2;
			x = r_hours * Ogre::Math::Cos(theta);
			y = r_hours * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dHourNode", i);

			tempSphere = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
			tempSphere->setMaterialName(hoursMaterialName);

			tempNode = hoursNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x));
			tempNode->scale(scaleHours, scaleHours, scaleHours);
			tempNode->attachObject(tempSphere);
			//tempNode->setVisible(false);
			mHourNodes.push_back(tempNode);
		}

		for (int i  = 0; i < minutes; i++) {
			theta = i/(float)minutes * Ogre::Math::PI * 2;
			x = r_minutes * Ogre::Math::Cos(theta);
			y = r_minutes * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dMinuteNode", i);

			tempSphere = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
			tempSphere->setMaterialName(minutesMaterialName);

			tempNode = minutesNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x));
			tempNode->scale(scaleMinutes, scaleMinutes, scaleMinutes);
			tempNode->attachObject(tempSphere);
			mMinuteNodes.push_back(tempNode);
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
	Ogre::SceneNode* hoursNode;
	Ogre::SceneNode* minutesNode;

	Clock* mClock;
	std::vector <Ogre::SceneNode*> mHourNodes;
	std::vector <Ogre::SceneNode*> mMinuteNodes;
};

#endif