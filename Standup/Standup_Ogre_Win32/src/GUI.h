
#ifndef __GUI_h_
#define __GUI_h_

#include "stdafx.h"
#include "GUI.h"
#include "OgreFrameListener.h"
#include <sstream>
#include <string>

using namespace CEGUI;

class GUI : public Ogre::FrameListener
{
public:
	GUI(void): FrameListener(){
		moveLeft = false;
		moveRight = false;
		isAlarmActive = false;
		swiftCounter =0;
	};
	~GUI(void){};
		void createScene(void);

	/************************************************************************/
	/* Events                                                               */
	/************************************************************************/
	bool swiftRight(const CEGUI::EventArgs& /*e*/) 
	{
		moveRight = true;
		return true;
	};

	bool swiftLeft(const CEGUI::EventArgs& /*e*/) 
	{
		moveLeft = true;
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

	bool scrollPositionChanged(const CEGUI::EventArgs& /*e*/){
			//if(lastSliderValue < dialog2Slider->getCurrentValue())
			//{
			//	scrollPositionChange = -1;
			//}
			//else if (lastSliderValue > dialog2Slider->getCurrentValue())
			//{
			//	scrollPositionChange = 1;
			//}
			//else
			//{
			//	scrollPositionChange = 0;
			//}
			//lastSliderValue = dialog2Slider->getCurrentValue();

		//dialog2Slider->setCurrentValue(dialog2Slider->get)
			return true;
		
	};

	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	int GUI::getSliderValueMin(float f);
	int GUI::getSliderValueHour(float f);
	String getSliderTimeString(float f);

private:
	FrameWindow* dialogWindow1;
	FrameWindow* dialogWindow2;
	FrameWindow* dialogWindow3;
	DefaultWindow* dialog2AlarmTime;
	DefaultWindow* dialog2ActivateText;
	Checkbox* dialog2Checkbox;
	Slider* dialog2Slider;
	Window* myRoot;
	bool moveLeft;
	bool moveRight;
	bool isAlarmActive;
	int swiftCounter;

	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderTarget *mRenderTarget;
	Ogre::Viewport* mViewport;


};

#endif // #ifndef __GUI_h_
