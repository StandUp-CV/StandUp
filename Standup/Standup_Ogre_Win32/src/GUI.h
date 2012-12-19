
#ifndef __GUI_h_
#define __GUI_h_

#include "stdafx.h"
#include "GUI.h"
#include "OgreFrameListener.h"
#include <sstream>
#include <string>
#include "AnimationBuilder.h"
#include "Clock.h"
#include "fmod.hpp"
#include "Sound.h"

using namespace CEGUI;

// Class that handles the gui creation and animation
class GUI : public Ogre::FrameListener , public AlarmEventHandler
{
public:

	void watchOutEvent()
	{
		mPrerunSound->play();
	}
	void alarmEvent()
	{
		mAlarmSound->play();
	}
	void stopRingingEvent() { }
	void everythingCompleteEvent() { }

	//! Constructor GUI
	/*!
		Create Object
		set initial value of members
	*/
	GUI(CEGUI::System* system, Ogre::Root* root) : FrameListener() {
		mMoveLeft = false;
		mMoveRight = false;
		mIsAlarmActive = false;
		mSystem = system;
		mAlarmSound = new Sound();
		mPrerunSound = new Sound();
		mPrerunSound->reloadSoundFile("stuka.wav");
		root->addFrameListener(mAlarmSound);
		root->addFrameListener(mPrerunSound);
	};

	//! Destructor GUI
	/*!
	*/
	~GUI(void){ mSystem = NULL; };

	void registerAlarmClock(AlarmClock* ac) { mAlarmClock=ac; }


	//! Create the CEGUI Scene
	/*!
		Create WindowManager to create CEGUI Windows and set the root Window Node
	*/
	void createScene(void);

	//! Create the CEGUI Components in Dialog1 - middle Decorative view
	/*!
		Create all Components in Dialog1 and set permanent porperties
	*/
	void createDialog1( WindowManager &wmgr );

	//! Create the CEGUI Components in Dialog2 - Leftside Alarm settings
	/*!
		Create all Components in Dialog2 and set permanent porperties
	*/
	void createDialog2( WindowManager &wmgr );

	//! Create the CEGUI Components in Dialog3 - Rightside alternative Clockview
	/*!
		Create all Components and RTT-texture in Dialog3 and set permanent porperties
	*/
	void createDialog3( WindowManager &wmgr );

	//! create CEGUI_RTT Scene in Dialog3
	/*!
		Contains alternative Clock view (clockvisualisationBars)
	*/
	Ogre::TexturePtr createCEGUI_RTTScene();

	//! Creates all Animation Instances used for GUI Animations
	/*!
		get all Animations created in AnimationBuilder
	*/
	void setAnimationInstances() 
	{
		/************************************************************************/
		/* -----------------------ANIMATION-------------------------------------*/
		/************************************************************************/

		mAnimationBuilder->createAnimations(mDialogWindow1->getProperty("UnifiedXPosition"),
			mDialogWindow2->getProperty("UnifiedXPosition"), 
			mDialogWindow3->getProperty("UnifiedXPosition"), 
			mDialogWindow1->getProperty("YRotation"),
			mDialogWindow2->getProperty("YRotation"),
			mDialogWindow3->getProperty("YRotation")
			);
		AnimationManager& animMng = AnimationManager::getSingleton();

		// Animation Instances used in Dialog1
		instAnim_MoveWindow1Left = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow1Left"));//AnimationInstances get and setTarget
		instAnim_MoveWindow1Left->setTargetWindow(mDialogWindow1);
		instAnim_MoveWindow1Right = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow1Right"));
		instAnim_MoveWindow1Right->setTargetWindow(mDialogWindow1);
		instAnim_moveWindow1FromLeftToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow1FromLeftToStart"));
		instAnim_moveWindow1FromLeftToStart->setTargetWindow(mDialogWindow1);
		instAnim_moveWindow1FromRightToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow1FromRightToStart"));
		instAnim_moveWindow1FromRightToStart->setTargetWindow(mDialogWindow1);
		instAnim_FadeIn1 = animMng.instantiateAnimation(animMng.getAnimation("FadeIn1"));
		instAnim_FadeOut = animMng.instantiateAnimation(animMng.getAnimation("FadeOut"));

		// Animation Instances used in Dialog2
		instAnim_MoveWindow2Right= animMng.instantiateAnimation(animMng.getAnimation("MoveWindow2Right")); //AnimationInstances get and setTarget
		instAnim_MoveWindow2Right->setTargetWindow(mDialogWindow2);
		instAnim_moveWindow2FromLeftToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow2FromLeftToStart"));
		instAnim_moveWindow2FromLeftToStart->setTargetWindow(mDialogWindow2);

		// Animation Instances used in Dialog3
		instAnim_MoveWindow3Left = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow3Left"));
		instAnim_MoveWindow3Left->setTargetWindow(mDialogWindow3);
		instAnim_moveWindow3FromRightToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow3FromRightToStart"));
		instAnim_moveWindow3FromRightToStart->setTargetWindow(mDialogWindow3);

	}



	/************************************************************************/
	/* Events                                                               */
	/************************************************************************/
	
	//! THe Event Handling when mDialog1ButtonLeft is clicked
	/*!
		start YRotation and UnifiedXPosition-Change Animation
	\param Event CEGUI::PushButton::EventClicked
	\return true
	*/
	bool dialog1ButtonLeftClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_MoveWindow1Right->start();
		instAnim_MoveWindow2Right->start();
		mMoveRight = true;
		return true;
	};

	//! THe Event Handling when mDialog1ButtonRight is clicked
	/*!
		start YRotation and UnifiedXPosition-Change Animation
	\param Event CEGUI::PushButton::EventClicked
	\return true
	*/
	bool dialog1ButtonRightClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_MoveWindow1Left->start();
		instAnim_MoveWindow3Left->start();
		mMoveLeft = true;
		return true;
	};

	//! THe Event Handling when mDialog2ButtonRight is clicked
	/*!
	start YRotation and UnifiedXPosition-Change Animation
	\param Event CEGUI::PushButton::EventClicked
	\return true
	*/
	bool dialog2ButtonRightClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_moveWindow1FromRightToStart->start();
		instAnim_moveWindow2FromLeftToStart->start();
		return true;
	};

	//! THe Event Handling when mDialog3ButtonLeft is clicked
	/*!
	start YRotation and UnifiedXPosition-Change Animation
	\param Event CEGUI::PushButton::EventClicked
	\return true
	*/
	bool dialog3ButtonLeftClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_moveWindow1FromLeftToStart->start();
		instAnim_moveWindow3FromRightToStart->start();
		return true;
	};

	//! THe Event Handling when the Value of the mDialog2CheckBox changed
	/*!
	change Text in mDialog2StateInfo
	\param Event CEGUI::PushButton::EventCheckStateChanged
	\return true
	*/
	bool checkBoxClicked(const CEGUI::EventArgs& /*e*/) 
	{
		mIsAlarmActive=!mIsAlarmActive;	
		mAlarmClock->setActive(mIsAlarmActive);
		mDialog2Slider->setEnabled(!mIsAlarmActive);
		if(!mIsAlarmActive)
		{	
			mDialog2StateInfo->setText("Please choose wakeup time and press activate.");
		}
		else
		{	
			mDialog2StateInfo->setText("The wakeup alarm is active.");
			//TODO PersonState Info, when alarm starts
		}
		return true;
	};

	//! THe Event Handling when the Mouse Hover in a button Area 
	/*!
	start Animation Fade In (Alpha from "0.0" to "0.3")
	\param Event CEGUI::PushButton::EventMouseEntersArea
	\return true
	*/
	bool dialog1ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/)
	{
			instAnim_FadeIn1->setTargetWindow(mDialog1ButtonLeft);
			instAnim_FadeIn1->start();
			return true;
	}

	//! THe Event Handling when the Mouse Hover in a button Area 
	/*!
	start Animation Fade In (Alpha from "0.0" to "0.3")
	\param Event CEGUI::PushButton::EventMouseEntersArea
	\return true
	*/
	bool dialog1ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeIn1->setTargetWindow(mDialog1ButtonRight);
		instAnim_FadeIn1->start();
		return true;
	}

	//! THe Event Handling when the Mouse Hover in a button Area 
	/*!
	start Animation Fade In (Alpha from "0.0" to "0.3")
	\param Event CEGUI::PushButton::EventMouseEntersArea
	\return true
	*/
	bool dialog2ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeIn1->setTargetWindow(mDialog2ButtonRight);
		instAnim_FadeIn1->start();
		return true;
	}

	//! THe Event Handling when the Mouse Hover in a button Area 
	/*!
	start Animation Fade In (Alpha from "0.0" to "0.3")
	\param Event CEGUI::PushButton::EventMouseEntersArea
	\return true
	*/
	bool dialog3ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeIn1->setTargetWindow(mDialog3ButtonLeft);
		instAnim_FadeIn1->start();
		return true;
	}

	//! THe Event Handling when the Mouse Hover out a button Area 
	/*!
	start Animation Fade In (Alpha from "0.3" to "0.0")
	\param Event CEGUI::PushButton::EventMouseLeavesArea
	\return true
	*/	
	bool dialog1ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeOut->setTargetWindow(mDialog1ButtonLeft);
		instAnim_FadeOut->start();
		return true;
	}

	//! THe Event Handling when the Mouse Hover out a button Area 
	/*!
	start Animation Fade In (Alpha from "0.3" to "0.0")
	\param Event CEGUI::PushButton::EventMouseLeavesArea
	\return true
	*/	
	bool dialog1ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeOut->setTargetWindow(mDialog1ButtonRight);
		instAnim_FadeOut->start();
		return true;
	}

	//! THe Event Handling when the Mouse Hover out a button Area 
	/*!
	start Animation Fade In (Alpha from "0.3" to "0.0")
	\param Event CEGUI::PushButton::EventMouseLeavesArea
	\return true
	*/	
	bool dialog2ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeOut->setTargetWindow(mDialog2ButtonRight);
		instAnim_FadeOut->start();
		return true;
	}

	//! THe Event Handling when the Mouse Hover out a button Area 
	/*!
	start Animation Fade In (Alpha from "0.3" to "0.0")
	\param Event CEGUI::PushButton::EventMouseLeavesArea
	\return true
	*/	
	bool dialog3ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeOut->setTargetWindow(mDialog3ButtonLeft);
		instAnim_FadeOut->start();
		return true;
	}

	//! renders the gui, handles RTT issues
	/*!
	\param frame Event 
	\return true
	*/	
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);


	//! used in methode frameRenderingQueued 
	/*!
	\param frame Event
	*/	
	void update(const Ogre::FrameEvent& evt);

	//! getSliderValueMin used in getSliderTimeString
	/*!
	 \param float Slider->CurrentValue [0,1]
	 \return int min [0,59]
	*/	
	int GUI::getSliderValueMin(float f);

	//! getSliderValueHour used in getSliderTimeString
	/*!
	 \param float Slider->CurrentValue [0,1]
	 \return int hour [0,23]
	*/	
	int GUI::getSliderValueHour(float f);

	//! getSliderTimeString used to update the AlarmClock Dialog
	/*!
	 \param float Slider->CurrentValue [0,1]
	 \return String (ex.: 12:23)
	*/	
	String getSliderTimeString(float f);

	//! getCurrentTimeString used to update the CurrentTime Dialog
	/*!
	get Current Time from System clock
	 \return String (ex.: 12:23)
	*/	
	String getCurrentTimeString(void);

private:
	void initialiseRTTViewport(CEGUI::RenderingSurface* const surface);
	float getCurrentTimePosition();
	CEGUI::System* mSystem;

	FrameWindow* mDialogWindow1;
	FrameWindow* mDialogWindow2;
	FrameWindow* mDialogWindow3;
	FrameWindow* mainWindow;
	DefaultWindow* mDialog2AlarmTime;
	DefaultWindow* mDialog2CurrentTime;
	DefaultWindow* mDialog2StateInfo;
	DefaultWindow* mDialog1TextClock;
	DefaultWindow* mDialog1TextAlarm;
	DefaultWindow* mDialog2CurrentTimeHelper;
	DefaultWindow* mDialog2Clock;
	PushButton* mDialog1ButtonRight;
	PushButton* mDialog1ButtonLeft;
	PushButton* mDialog3ButtonLeft;
	PushButton* mDialog2ButtonRight ;
	Checkbox* mDialog2Checkbox;
	Slider* mDialog2Slider;
	Window* mWindowRoot;
	bool mMoveLeft;
	bool mMoveRight;
	bool mIsAlarmActive;
	// saves the current time and gmt offset
	int mCurrentSeconds;
	int mCurrentMinutes;
	int mCurrentHours;
	int mHourFormat;
	int mAlarmMinutes;
	int mAlarmHours;

	Ogre::Camera* mCamera;
	Ogre::SceneManager* mRTTSceneMgr;
	Ogre::RenderTarget *mRenderTarget;
	Ogre::Viewport* mViewport;

	AnimationBuilder* mAnimationBuilder;
	// AnimationInstance
	AnimationInstance* instAnim_MoveWindow1Right;
	AnimationInstance* instAnim_MoveWindow2Right;
	AnimationInstance* instAnim_MoveWindow1Left;
	AnimationInstance* instAnim_MoveWindow3Left;
	AnimationInstance* instAnim_moveWindow1FromRightToStart;
	AnimationInstance* instAnim_moveWindow2FromLeftToStart;
	AnimationInstance* instAnim_moveWindow1FromLeftToStart;
	AnimationInstance* instAnim_moveWindow3FromRightToStart;
	AnimationInstance* instAnim_FadeIn1;
	AnimationInstance* instAnim_FadeOut;


	AlarmClock* mAlarmClock;

	//RTT Utils
	Ogre::Viewport *mRTTViewport;
	Ogre::Camera *mRTTCam;
	Ogre::RenderTexture *mOgreRenderTexture;	
	// the reference to the class that handles mAlarmSound
	Sound* mAlarmSound;
	Sound* mPrerunSound;
};

#endif // #ifndef __GUI_h_
