
#ifndef __GUI_h_
#define __GUI_h_

#include "stdafx.h"
#include "GUI.h"
#include "OgreFrameListener.h"
#include <sstream>
#include <string>
#include "AnimationBuilder.h"
#include "Clock.h"

using namespace CEGUI;

class GUI : public Ogre::FrameListener
{
public:
	GUI(void): FrameListener(){
		moveLeft = false;
		moveRight = false;
		isAlarmActive = false;
	};
	~GUI(void){};
		void createScene(void);

	/************************************************************************/
	/* Events                                                               */
	/************************************************************************/
	bool dialog1ButtonLeftClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_MoveWindow1Right->start();
		instAnim_MoveWindow2Right->start();
		moveRight = true;
		return true;
	};

	bool dialog1ButtonRightClicked(const CEGUI::EventArgs& /*e*/) 
	{
		instAnim_MoveWindow1Left->start();
		instAnim_MoveWindow3Left->start();
		moveLeft = true;
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
		if(isAlarmActive){
					isAlarmActive = false;
		}
		else
		{
					isAlarmActive = true;
		}
		return true;
	};
	

	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	int GUI::getSliderValueMin(float f);
	int GUI::getSliderValueHour(float f);
	String getSliderTimeString(float f);
	String getCurrentTimeString(void);

	//String getCurrentAlarmTimeString(void);
private:
	FrameWindow* dialogWindow1;
	FrameWindow* dialogWindow2;
	FrameWindow* dialogWindow3;
	FrameWindow* mainWindow;
	DefaultWindow* dialog2AlarmTime;
	DefaultWindow* dialog2ActivateText;
	DefaultWindow* dialog1TextClock;
	DefaultWindow* dialog1TextAlarm;
	Checkbox* dialog2Checkbox;
	Slider* dialog2Slider;
	Window* myRoot;
	bool moveLeft;
	bool moveRight;
	bool isAlarmActive;
	// saves the current time and gmt offset
	int mCurrentSeconds;
	int mCurrentMinutes;
	int mCurrentHours;
	int mHourFormat;
	int mAlarmMinutes;
	int mAlarmHours;

	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderTarget *mRenderTarget;
	Ogre::Viewport* mViewport;

	AnimationBuilder* animBuilder;
	// AnimationInstance
	AnimationInstance* instAnim_MoveWindow1Right;
	AnimationInstance* instAnim_MoveWindow2Right;
	AnimationInstance* instAnim_MoveWindow1Left;
	AnimationInstance* instAnim_MoveWindow3Left;
	AnimationInstance* instAnim_moveWindow1FromRightToStart;
	AnimationInstance* instAnim_moveWindow2FromLeftToStart;
	AnimationInstance* instAnim_moveWindow1FromLeftToStart;
	AnimationInstance* instAnim_moveWindow3FromRightToStart;

	Clock* mClock;
	AlarmClock* mAlarmClock;
};

#endif // #ifndef __GUI_h_
