#ifndef CLOCK_VISUALIZATION_CIRCLE_H
#define CLOCK_VISUALIZATION_CIRCLE_H

#include "stdafx.h"
#include <vector>
#include <OgreFrameListener.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreMath.h"
#include "clock.h"
#include "OgreQuaternion.h"
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
		Ogre::Camera* cam, int hourFormat = 1) : ClockVisualization(sceneManager, hourFormat), 
		mCamera(cam) {
		// set max values
		mHours = 12 * mHourFormat;
		mMinutes = 60;
		mSeconds = 60;
		// create the clock components
		createClock();
		// get the initial time
		const tm& localTime = Clock::getDisplayTime(Clock::getCurrentSecond());
		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % (12 * mHourFormat);
		mAnimationTime = 0;
		// create ambient light for daytime depented lighting
		mDaytimeLight = mSceneMgr->createLight("ClockAmbientLight");
		mDaytimeLight->setType(Ogre::Light::LT_POINT);
		mDaytimeLight->setCastShadows(true);
		mDaytimeLight->setPosition(*(mLightPosition = new Ogre::Vector3(20,100,0)));
		//mDaytimeLight->setAttenuation(1000, 0.f, 1.0f, 1.f);
		// set initial cam distance and alginment in front of mMinutes plane
		mCameraPosition = Ogre::Vector3(0,15,-66);
	}

	//-------------------------------------------------------------------------------------
	//Updates the clock continously for each frame.
	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
		//////////////////////////////////////////////////////////////////////////
		//		DEBUG
		////////////////////////////////////////////////////////////////////////// 
		//static float dayInterpolationTime=0.0f;
		//mAnimationTime += (evt.timeSinceLastEvent);
		//dayInterpolationTime+=evt.timeSinceLastEvent;
		//if(dayInterpolationTime>24.0f) dayInterpolationTime-=24.0f;
		//////////////////////////////////////////////////////////////////////////

		// counter for slowed clock update (needs only once per second ;)
		static int second=-1;
		// step forwad in time for animation
		mAnimationTime += (evt.timeSinceLastEvent);
		// get current time from clock
		const tm& localTime = Clock::getDisplayTime(Clock::getCurrentSecond());
		float dayInterpolationTime = localTime.tm_hour + (localTime.tm_min * 0.01667f);
		// get the current secs, mins and mHours
		mCurrentSeconds = localTime.tm_sec;
		mCurrentMinutes = localTime.tm_min;
		mCurrentHours = localTime.tm_hour % (12 * mHourFormat); // in right time format (12 vs 24)

		// Apply Time visualization every second
		if(mCurrentSeconds!=second)
		{
			second = mCurrentSeconds;
			//mDaytimeLight->setSpecularColour(newColor);
			// Seconds
			for (int i = 0; i < mSeconds; i++) {
				//mVectorSecondGeom[i]->setVisible(i!=mCurrentSeconds);
				Ogre::Entity* node = mVectorSecondGeom[(i+mSeconds/4) % mSeconds];
				node->setMaterialName(i < mCurrentSeconds?"Standup/Clock/Cubemap_Seconds":"Standup/Clock/Cubemap_Trans");
				node->setCastShadows(i < mCurrentSeconds);
			}

			// Minutes
			for (int i = 0; i < mMinutes; i++) {
				//mVectorMinuteGeom[i]->setVisible(i < mCurrentMinutes);
				Ogre::Entity* node = mVectorMinuteGeom[(i+mMinutes/4) % mMinutes];
				node->setMaterialName(i < mCurrentMinutes?"Standup/Clock/Cubemap_Minutes":"Standup/Clock/Cubemap_Trans");
				node->setCastShadows(i < mCurrentMinutes);
			}
			// Hours
			for (int i = 0; i < mHours; i++) {
				//mVectorHourGeom[i]->setVisible(i < mCurrentHours);
				Ogre::Entity* node = mVectorHourGeom[(i+mHours/4) % mHours];
				node->setMaterialName(i < mCurrentHours ? "Standup/Clock/Cubemap_Hours" : "Standup/Clock/Cubemap_Trans");
				node->setCastShadows(i < mCurrentHours);
			}
		}
		// Light Color interpolate
		Ogre::ColourValue newColor = interpolateColors(dayInterpolationTime);//localTime.tm_hour + (localTime.tm_min * 0.01667f));
		mDaytimeLight->setDiffuseColour(newColor);
		mDaytimeLight->setSpecularColour(newColor);
		// light position update animation
		// 
		float speed = (mAnimationTime * 0.2f);
		float x = 10 * Ogre::Math::Cos(Ogre::Math::PI * 2 * speed);
		float z = 10 * Ogre::Math::Sin(Ogre::Math::PI * 2 * speed);
		float y;
		mLightPosition->x = x;
		mLightPosition->z = z;
		mDaytimeLight->setPosition(*(mLightPosition));

		// Animate the clock via rotation
		// Rotation of hours, minutes and seconds
		Ogre::Quaternion q1,q2,q3;
		float hoursTime = mAnimationTime * (1.0f/3600.0f);
		mHoursNode->setOrientation(q1=Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * hoursTime * 2.0f), Ogre::Vector3::NEGATIVE_UNIT_Y));
		float minutesTime = mAnimationTime * (1.0f/60.0f);
		mMinutesNode->setOrientation(q2=Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * minutesTime * 2.0f), Ogre::Vector3::UNIT_Y));
		float secondsTime = mAnimationTime * 0.2f;
		mSecondsNode->setOrientation(q3=Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * secondsTime * 2.0f), Ogre::Vector3::UNIT_Z));
		// camera rotation
		Ogre::Matrix3 m1;
		Ogre::Matrix3 m2;

		Ogre::Matrix3 rm; 
		rm.FromAngleAxis(Ogre::Vector3::NEGATIVE_UNIT_Z, Ogre::Radian(Ogre::Math::PI*0.5f));
		Ogre::Matrix3 rm2; 
		rm2.FromAngleAxis(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Math::PI*0.5f));

		q1.ToRotationMatrix(m1);
		q2.ToRotationMatrix(m2);
		Ogre::Matrix4 m4 = Ogre::Matrix4( (m1*m2*rm2).Inverse());
		m4.setTrans(mCameraPosition);
		mCamera->setCustomViewMatrix(true, m4);
		return true;
	}
private:
	//-------------------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------
	// interpolates a colour value by given Daytime from 0f - 24f
	Ogre::ColourValue interpolateColors(float time) {

		// colours.h contains unsigned char interpolationTable[768]
		// holding 256 rgb triplets
		// 
		#include "colours.h"
		
		float scaledTime = time*(256.0f/24.0f);
		int tableindex=(int)scaledTime;
		float t = scaledTime-(float)tableindex;
		// linear interpolation between two neighbouring table entries
		return Ogre::ColourValue(((float)interpolationTable[tableindex*3+0]*(1-t)+(float)interpolationTable[(tableindex*3+3)%768]*t)*(1.0f/256.0f),
								 ((float)interpolationTable[tableindex*3+1]*(1-t)+(float)interpolationTable[(tableindex*3+4)%768]*t)*(1.0f/256.0f),
								 ((float)interpolationTable[tableindex*3+2]*(1-t)+(float)interpolationTable[(tableindex*3+5)%768]*t)*(1.0f/256.0f), 1);
	}
	//-------------------------------------------------------------------------------------
	// Creates the clocks base-components initially
	void createClock() {
		Ogre::SceneNode* rootNode = mSceneMgr->getRootSceneNode();

		mClockNode = rootNode->createChildSceneNode("MainCircleClockNode");
		mClockNode->setPosition(0,0,0);
		mMiddleSphereNode = mClockNode->createChildSceneNode("ClockRotationNode");
		//mClockNode->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Math::PI * 0.5f), Ogre::Vector3::NEGATIVE_UNIT_Z));
		mHoursNode = mClockNode->createChildSceneNode("HoursNode");
		mMinutesNode = mHoursNode->createChildSceneNode("MinutesNode");
		mSecondsNode = mMinutesNode->createChildSceneNode("SecondsNode");

		Ogre::Entity* sphere = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
		sphere->setMaterialName("Standup/Clock/Cubemap_Hours");
		sphere->setCastShadows(false);
		mMiddleSphereNode->attachObject(sphere);
		mMiddleSphereNode->setScale(0.2,0.2,0.2);

		Ogre::SceneNode* tempNode;
		Ogre::Entity* tempGeometry;
		Ogre::String hoursMaterialName = "Standup/Clock/Cubemap_Hours";
		Ogre::String minutesMaterialName = "Standup/Clock/Cubemap_Minutes";
		Ogre::String secondsMaterialName = "Standup/Clock/Cubemap_Seconds";

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

		for (int i  = 0; i < mHours; i++) {
			theta = i/(float)mHours * Ogre::Math::PI * 2;
			x = r_hours * Ogre::Math::Cos(theta);
			y = r_hours * Ogre::Math::Sin(theta);
			sprintf(numstr, "%dHourNode", i);

			tempGeometry = mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
			tempGeometry->setMaterialName(hoursMaterialName);
			tempGeometry->setCastShadows(true);

			tempNode = mHoursNode->createChildSceneNode(numstr, Ogre::Vector3(0, y, x), 
				Ogre::Quaternion(Ogre::Radian(theta), Ogre::Vector3::NEGATIVE_UNIT_X));

			float rscale = scaleHours;
			if((i%(3 * mHourFormat))!=0) rscale*=0.66f;
			tempNode->setScale(rscale, rscale, rscale);
			tempNode->attachObject(tempGeometry);
			//tempNode->setVisible(false);
			mVectorHourGeom.push_back(tempGeometry);
		}

		for (int i  = 0; i < mMinutes; i++) {
			theta = i/(float)mMinutes * Ogre::Math::PI * 2;
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
			tempNode->setScale(rscale, rscale, rscale);
			tempNode->attachObject(tempGeometry);
			mVectorMinuteGeom.push_back(tempGeometry);
		}

		for (int i  = 0; i < mSeconds; i++) {
			theta = i/(float)mSeconds * Ogre::Math::PI * 2.0f;
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
			tempNode->setScale(rscale, rscale, rscale*5.0f);
			tempNode->attachObject(tempGeometry);
			mVectorSecondGeom.push_back(tempGeometry);
		}
		//Ogre::SceneNode* zeroNode = mClockNode->createChildSceneNode("ZeroNode", Ogre::Vector3(0, 20, 0));
		//zeroNode->scale(0.05f, 0.05f, 0.05f);
		//zeroNode->attachObject(sphere);
	}

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