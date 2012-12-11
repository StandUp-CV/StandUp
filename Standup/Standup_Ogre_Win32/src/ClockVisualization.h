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
	ClockVisualization(const Ogre::String &name, Ogre::SceneManager* sceneManager, Clock* clock, Ogre::Camera* cam, int hourFormat = 1) 
		: mSceneMgr(sceneManager), mClock(clock), mHourFormat(hourFormat) {
		createClock();
		mCamera=cam;
		const tm& localTime = mClock->getDisplayTime(mClock->getCurrentSecond());
		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % 12;
		mTime = 0;
		//light
		mAmbientLight = mSceneMgr->createLight("ClockAmbientLight");
		mAmbientLight->setType(Ogre::Light::LT_POINT);
		mAmbientLight->setCastShadows(true);
		mAmbientLight->setPosition(0, 55, 0);
		//mAmbientLight->set
		//mAmbientLight->setDiffuseColour(Ogre::ColourValue(1,1,1,1));
	}

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		static int second=-1;
		static float testTime=0.0f;
		mTime += (evt.timeSinceLastEvent);
		testTime+=evt.timeSinceLastEvent;
		if(testTime>24.0f) testTime-=24.0f;

		const tm& localTime = mClock->getDisplayTime(mClock->getCurrentSecond());

		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % (12 * mHourFormat);

		// Light Color interpolate
		Ogre::ColourValue newColor = interpolateColors(testTime);//localTime.tm_hour + (localTime.tm_min * 0.01667f));
		mAmbientLight->setDiffuseColour(newColor);
		// Apply Time visualization every second
		if(mCurrentSeconds!=second)
		{
			second=mCurrentSeconds;
			//mAmbientLight->setSpecularColour(newColor);
			// Seconds
			for (int i = 0; i < 60; i++) {
				//mVectorSecondNodes[i]->setVisible(i!=mCurrentSeconds);
				Ogre::Entity* node = static_cast<Ogre::Entity*>(mVectorSecondNodes[(i+15)%60]->getAttachedObject(0));
				node->setMaterialName(i < mCurrentSeconds?"Standup/Clock/Cubemap_Seconds":"Standup/Clock/Cubemap_Trans");
				node->setCastShadows(i < mCurrentSeconds);
			}

			// Minutes
			for (int i = 0; i < 60; i++) {
				//mVectorMinuteNodes[i]->setVisible(i < mCurrentMinutes);
				Ogre::Entity* node = static_cast<Ogre::Entity*>(mVectorMinuteNodes[(i+15)%60]->getAttachedObject(0));
				node->setMaterialName(i < mCurrentMinutes?"Standup/Clock/Cubemap_Minutes":"Standup/Clock/Cubemap_Trans");
				node->setCastShadows(i < mCurrentMinutes);
			}
			// Hours
			for (int i = 0; i < (12 * mHourFormat); i++) {
				//mVectorHourNodes[i]->setVisible(i < mCurrentHours);
				Ogre::Entity* node = static_cast<Ogre::Entity*>(mVectorHourNodes[(i+(3 * mHourFormat))%(12 * mHourFormat)]->getAttachedObject(0));
				node->setMaterialName(i < mCurrentHours?"Standup/Clock/Cubemap_Hours":"Standup/Clock/Cubemap_Trans");
				node->setCastShadows(i < mCurrentHours);
			}
		}

		// Animate the clock via rotation
		float x;
		float y;
		float z;

		float mainTime = 0.3f*mTime;
		// Base Clock Rotation
		//y = 0.1f * Ogre::Math::Sin((mainTime) * 2.0f * Ogre::Math::PI);
		//z = 0.1f * Ogre::Math::Cos((mainTime) * 2.0f * Ogre::Math::PI);
		//mClockRotationNode->setOrientation(Ogre::Quaternion(1,0,y,z));
		// Minutes Rotation
		
		Ogre::Quaternion q1,q2,q3;
		float hoursTime = mTime * (1.0f/3600.0f);
		mHoursNode->setOrientation(q1=Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * hoursTime * 2.0f), Ogre::Vector3::NEGATIVE_UNIT_Y));
		float minutesTime = mTime * (1.0f/60.0f);
		mMinutesNode->setOrientation(q2=Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * minutesTime * 2.0f), Ogre::Vector3::UNIT_Y));
		float secondsTime = mTime*0.25f;
		mSecondsNode->setOrientation(q3=Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * secondsTime * 2.0f), Ogre::Vector3::UNIT_Z));
		//if (mTime > 2) mTime = 0;
		// 

		Ogre::Matrix3 m1;
		Ogre::Matrix3 m2;
		Ogre::Matrix3 m3;
		Ogre::Matrix3 rm; rm.FromAngleAxis(Ogre::Vector3::NEGATIVE_UNIT_Z, Ogre::Radian(Ogre::Math::PI*0.5f));
		Ogre::Matrix3 rm2; rm2.FromAngleAxis(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Math::PI*0.5f));
		q1.ToRotationMatrix(m1);
		q2.ToRotationMatrix(m2);
		q3.ToRotationMatrix(m3);
		Ogre::Matrix4 m4 = Ogre::Matrix4( (m1*m2*rm2).Inverse());
		m4.setTrans(Ogre::Vector3(0,10,-45));
		//m4=m4.inverse();
		mCamera->setCustomViewMatrix(true, m4);
		// return
		return true;
	}
private:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------
	//float getInterploationParam(float baseTime) {
//
	//}

	Ogre::ColourValue interpolateColors(float time) {

		// colours.h contains unsigned char interpolationTable[768]
		// holding 256 rgb triplets
		// 
		#include "colours.h"

		float scaledTime = time*(256.0f/24.0f);
		int tableindex=(int)scaledTime;
		float t = scaledTime-(float)tableindex;

		//float time2 = (time * time);
		//float r = 0.083f * time2 - 2.33f * time + 15;
		//float g = -0.0625f * time2 + 1.625f * time - 9;
		//float b = 0.01667f * time2 - 0.33f * time + 1.6f;
		// 

		// linear interpolation between two neighbouring table entries

		return Ogre::ColourValue(((float)interpolationTable[tableindex*3+0]*(1-t)+(float)interpolationTable[(tableindex*3+3)%768]*t)*(1.0f/256.0f),
								 ((float)interpolationTable[tableindex*3+1]*(1-t)+(float)interpolationTable[(tableindex*3+4)%768]*t)*(1.0f/256.0f),
								 ((float)interpolationTable[tableindex*3+2]*(1-t)+(float)interpolationTable[(tableindex*3+5)%768]*t)*(1.0f/256.0f), 1);
	}

	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();

		mClockNode = rootNode->createChildSceneNode("MainClockNode");
		mClockRotationNode = mClockNode->createChildSceneNode("ClockRotationNode");
		//mClockNode->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * 0.5f), Ogre::Vector3::NEGATIVE_UNIT_Z));
		mHoursNode = mClockRotationNode->createChildSceneNode("HoursNode");
		mMinutesNode = mHoursNode->createChildSceneNode("MinutesNode");
		mSecondsNode = mMinutesNode->createChildSceneNode("SecondsNode");

		Ogre::SceneNode* tempNode;
		Ogre::Entity* tempGeometry;
		Ogre::String hoursMaterialName = "Standup/Clock/Cubemap_Hours";
		Ogre::String minutesMaterialName = "Standup/Clock/Cubemap_Minutes";
		Ogre::String secondsMaterialName = "Standup/Clock/Cubemap_Seconds";

		int hours = 12 * mHourFormat;
		int minutes = 60;
		int seconds = 60;
		float scaleHours = 0.05f;
		float scaleMinutes = 0.02f;
		float scaleSeconds = 0.005f;
		float x;
		float y;
		float theta;
		float r_hours = 25;
		float r_minutes = 20;
		float r_seconds = 15;
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

			float rscale = scaleHours;
			if((i%3)!=0) rscale*=0.66f;
			tempNode->scale(rscale, rscale, rscale);
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

			float rscale = scaleMinutes;
			if((i%5)!=0) rscale*=0.66f;
			tempNode->scale(rscale, rscale, rscale);
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

			float rscale = scaleSeconds;
			if((i%5)!=0) rscale*=0.66f;
			tempNode->scale(rscale, rscale, rscale*5.0f);
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
	int mHourFormat;
	float mTime;
	Ogre::Vector3* mRotating;
	Ogre::Quaternion* mRotatingQuat;
	Ogre::Camera* mCamera;

	Clock* mClock;
	std::vector <Ogre::SceneNode*> mVectorHourNodes;
	std::vector <Ogre::SceneNode*> mVectorMinuteNodes;
	std::vector <Ogre::SceneNode*> mVectorSecondNodes;
};

#endif