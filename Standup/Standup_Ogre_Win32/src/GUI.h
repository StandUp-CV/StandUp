
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


	GUI(CEGUI::System* system, Ogre::Root* root) : FrameListener() {
		mMoveLeft = false;
		mMoveRight = false;
		mIsAlarmActive = false;
		mSystem = system;
		mAlarmSound = new Sound();
		mPrerunSound = new Sound();
		mPrerunSound->reloadSoundFile("prerun.wav");
		root->addFrameListener(mAlarmSound);
		root->addFrameListener(mPrerunSound);
	};

	void registerAlarmClock(AlarmClock* ac) { mAlarmClock=ac; }

	~GUI(void){ mSystem = NULL; };

	void createScene(void);

	void createDialog1( WindowManager &wmgr );

	void createDialog2( WindowManager &wmgr );

	void createDialog3( WindowManager &wmgr );

	void setAnimationInstances() 
	{
		/************************************************************************/
		/* _-----------------------ANIMATION-------------------------------------*/
		/************************************************************************/

		mAnimationBuilder->createAnimations(mDialogWindow1->getProperty("UnifiedXPosition"),
			mDialogWindow2->getProperty("UnifiedXPosition"), 
			mDialogWindow3->getProperty("UnifiedXPosition"), 
			mDialogWindow1->getProperty("YRotation"),
			mDialogWindow2->getProperty("YRotation"),
			mDialogWindow3->getProperty("YRotation")
			);
		AnimationManager& animMng = AnimationManager::getSingleton();

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

		instAnim_MoveWindow2Right= animMng.instantiateAnimation(animMng.getAnimation("MoveWindow2Right")); //AnimationInstances get and setTarget
		instAnim_MoveWindow2Right->setTargetWindow(mDialogWindow2);
		instAnim_moveWindow2FromLeftToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow2FromLeftToStart"));
		instAnim_moveWindow2FromLeftToStart->setTargetWindow(mDialogWindow2);

		instAnim_MoveWindow3Left = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow3Left"));
		instAnim_MoveWindow3Left->setTargetWindow(mDialogWindow3);
		instAnim_moveWindow3FromRightToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow3FromRightToStart"));
		instAnim_moveWindow3FromRightToStart->setTargetWindow(mDialogWindow3);

		/************************************************************************/
		/* Animation            END                                             */
		/************************************************************************/
	}

	Ogre::TexturePtr createCEGUI_RTTScene();
	/************************************************************************/
	/* Events                                                               */
	/************************************************************************/
	bool dialog1ButtonLeftClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_MoveWindow1Right->start();
		instAnim_MoveWindow2Right->start();
		mMoveRight = true;
		return true;
	};

	bool dialog1ButtonRightClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_MoveWindow1Left->start();
		instAnim_MoveWindow3Left->start();
		mMoveLeft = true;
		return true;
	};

	bool dialog2ButtonRightClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_moveWindow1FromRightToStart->start();
		instAnim_moveWindow2FromLeftToStart->start();
		return true;
	};

	bool dialog3ButtonLeftClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_moveWindow1FromLeftToStart->start();
		instAnim_moveWindow3FromRightToStart->start();
		return true;
	};

	bool checkBoxClicked(const CEGUI::EventArgs& /*e*/) 
	{
		mIsAlarmActive=!mIsAlarmActive;
		
		mAlarmClock->setActive(mIsAlarmActive);

		mDialog2Slider->setEnabled(!mIsAlarmActive);

		return true;
	};

	bool dialog1ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/)
	{
				instAnim_FadeIn1->setTargetWindow(mDialog1ButtonLeft);
				instAnim_FadeIn1->start();
				return true;
	}

	bool dialog1ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeIn1->setTargetWindow(mDialog1ButtonRight);
		instAnim_FadeIn1->start();
		return true;
	}

	bool dialog2ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeIn1->setTargetWindow(mDialog2ButtonRight);
		instAnim_FadeIn1->start();
		return true;
	}

	bool dialog3ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeIn1->setTargetWindow(mDialog3ButtonLeft);
		instAnim_FadeIn1->start();
		return true;
	}

	
		bool dialog1ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/)
	{
		instAnim_FadeOut->setTargetWindow(mDialog1ButtonLeft);
		instAnim_FadeOut->start();
		return true;
	}

		bool dialog1ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/)
		{
			instAnim_FadeOut->setTargetWindow(mDialog1ButtonRight);
			instAnim_FadeOut->start();
			return true;
		}

		bool dialog2ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/)
		{
			instAnim_FadeOut->setTargetWindow(mDialog2ButtonRight);
			instAnim_FadeOut->start();
			return true;
		}

		bool dialog3ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/)
		{
			instAnim_FadeOut->setTargetWindow(mDialog3ButtonLeft);
			instAnim_FadeOut->start();
			return true;
		}

	// renders the gui, handles RTT issues
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	// updates the content
	void update(const Ogre::FrameEvent& evt);

	int GUI::getSliderValueMin(float f);
	int GUI::getSliderValueHour(float f);
	String getSliderTimeString(float f);
	String getCurrentTimeString(void);
	String getDisplayCurrentTime();
	//String getCurrentAlarmTimeString(void);
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
