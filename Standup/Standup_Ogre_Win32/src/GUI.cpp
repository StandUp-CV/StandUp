
/*
-----------------------------------------------------------------------------
Filename:    GUI.cpp
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
*/
#include "stdafx.h"
#include "GUI.h"
#include "Clock.h"
#include "CEGUISlider.h"
#include "OgreStringConverter.h"
#include "StandupApplication.h"
#include "ClockVisualizationBars.h"



void GUI::createScene( void )
{
	AlarmClock* alarm;

	// CEGUI
	WindowManager& wmgr = WindowManager::getSingleton();

	mWindowRoot = wmgr.createWindow( "DefaultWindow", "mWindowRoot" );
	System::getSingleton().setGUISheet( mWindowRoot );

	createDialog1(wmgr);
	createDialog2(wmgr);
	createDialog3(wmgr);

	setAnimationInstances();

}



// param realtive XPosition of Slider Thump [0,1]
// return int hours [0,23]
int GUI::getSliderValueHour(float f){
	
	int hourValue = (int)(24*f)%24;

	return hourValue;
}

// param realtive XPosition of Slider Thump [0,1]
// return int minutes [0,59]
int GUI::getSliderValueMin(float f){
	int minValue = (int)(24*60*f)%60;

	return minValue;
}

// param realtive XPosition of Slider Thump [0,1]
// return String (example 12:34) for mDialog2AlarmTime CEGUI Window
String GUI::getSliderTimeString(float f){

	int hour = getSliderValueHour(f);
	int min = getSliderValueMin(f);
	String s ="";
	if(hour<10)
		s += "0";
	s += Ogre::StringConverter::toString(hour) + ":";
	if(min<10)
		s+= "0";
	s+= Ogre::StringConverter::toString(min);
	return s;
}

//return current Time as String (example 12:34:56)
String GUI::getCurrentTimeString(void){
	// get current time from clock
	const tm& localTime = Clock::getDisplayTime(Clock::getCurrentSecond());
	// get the current secs, mins and mHours
	mCurrentSeconds = localTime.tm_sec;
	mCurrentMinutes = localTime.tm_min;
	mCurrentHours = localTime.tm_hour % (12 * mHourFormat); // in right time format (12 vs 24)
	String s ="";
	if(mCurrentHours<10)
		s += "0";
	s += Ogre::StringConverter::toString(mCurrentHours) + ":";
	if(mCurrentMinutes<10)
		s+= "0";
	s+= Ogre::StringConverter::toString(mCurrentMinutes);
// 	if(mCurrentSeconds<10)
// 		s+= "0";
// 		s+= Ogre::StringConverter::toString(mCurrentSeconds);
	return s;
}





float GUI::getCurrentTimePosition(){


	// get current time from clock
	const tm& localTime = Clock::getDisplayTime(Clock::getCurrentSecond());
	// get the current secs, mins and mHours
	float sec = localTime.tm_sec;
	float min = localTime.tm_min;
	float hour = localTime.tm_hour % (12 * mHourFormat); // in right time format (12 vs 24)
		float xPos = (float)((min/1440) + (hour/24)+ (sec/86400));
		xPos;
		return xPos;
}


//TODO
	//String GUI::getCurrentAlarmTimeString(){
	//	// get current alarm time from clock
	//	const tm& alarmTime = mClock->getDisplayTime(mAlarmClock->getAlarmTime());
	//	// get the alarm mins and mHours
	//	mAlarmMinutes = alarmTime.tm_min;
	//	mAlarmHours = alarmTime.tm_hour % (12 * mHourFormat); // in right time format (12 vs 24)
	//	String s ="";
	//	if(mAlarmHours<10)
	//		s += "0";
	//	s += Ogre::StringConverter::toString(mAlarmHours) + ":";
	//	if(mAlarmMinutes<10)
	//		s+= "0";
	//	s+= Ogre::StringConverter::toString(mAlarmMinutes) + ":";
	//	return s;
	//}

//Frame Rendering Queued
bool GUI::frameRenderingQueued( const Ogre::FrameEvent& evt )
{
	update(evt);

	// Only render when CEGUI is initialized
	if( &mSystem )
	{
		// get the targets to draw themselves.
		mDialogWindow3->invalidate(false);
		mOgreRenderTexture->update();

		// Now render the gui
		mSystem->renderGUI();
	}

	// True indicates that Ogre should continue rendering
	return true;
}



void GUI::update(const Ogre::FrameEvent& evt)
{
	int off=Clock::gmtoff();

	float alarmtime=mDialog2Slider->getCurrentValue();
	float day=(float)((Clock::getCurrentSecond())/Clock::DAY);

	try
	{
		mAlarmClock->setAlarmTime( (int) ( (day+alarmtime) * Clock::DAY + off) );
	}
	catch (ClockException& e42)
	{
		
	}


	mDialog2Clock->setText(getCurrentTimeString());

	//update position of mDialog2AlarmTime Window
	mDialog2AlarmTime->setPosition(((UVector2(UDim(0.15f,0),UDim(0.64f,0))) + (UVector2(UDim((alarmtime * 0.595f),0), UDim( 0, 0 )))));
	

	mDialog2Clock->setPosition(UVector2(UDim(0.15f,0),UDim(0.82f,0)) + (UVector2(UDim((getCurrentTimePosition()* 0.595f),0),UDim(0,0))));
	//
	mDialog2CurrentTime->setPosition((UVector2(UDim(0.205f,0),UDim(0.71f,0))) + (UVector2(UDim((getCurrentTimePosition()* 0.595f),0),UDim(0,0))));


	mDialog2CurrentTimeHelper->setSize( (UVector2(UDim(0,0),UDim(0.1f,0))) +(UVector2((UDim(alarmtime,0) * UDim(0.595f,0)), UDim(0,0))));
	//update Text of mDialog2AlarmTime (example 12:34)

	mDialog2AlarmTime->setText(getSliderTimeString(alarmtime));

	if(mDialog2CurrentTime->getXPosition().asRelative(1.0) <   ((UDim(0.205f,0) +(((UDim(alarmtime,0)) * UDim(0.595f,0)))).asRelative(1.0f))){
		mDialog2CurrentTimeHelper->setVisible(false);
		mDialog2CurrentTime->setSize(  (UVector2(UDim(0,0),UDim(0.1f,0))) -((UVector2(mDialog2CurrentTime->getXPosition() - UDim(0.2f,0), UDim(0,0)) - (UVector2(((UDim(alarmtime,0)) * UDim(0.595f,0)), UDim(0,0))))));
	}
	else{
		if(mDialog2Slider->getCurrentValue()!=0 )
			mDialog2CurrentTimeHelper->setVisible(true);
		else
		{
			mDialog2CurrentTimeHelper->setVisible(false);
		}
			mDialog2CurrentTime->setSize(  (UVector2(UDim(0,0),UDim(0.1f,0))) -((UVector2(mDialog2CurrentTime->getXPosition()- UDim(0.2f,0), UDim(0,0)) - (UVector2((UDim(1,0) * UDim(0.595f,0)), UDim(0,0))))));
	}

	// update 
	//mDialog2CurrentTime->setText(Ogre::StringConverter::toString(mDialog2Checkbox->isSelected()));

	//mDialog2CurrentTimeHelper->setText("current State");
}

Ogre::TexturePtr GUI::createCEGUI_RTTScene()
{
	mSceneMgr = StandupApplication::getInstance()->getRoot()->createSceneManager(Ogre::ST_GENERIC);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	ClockVisualizationBars* clockVis = 
		new ClockVisualizationBars(mSceneMgr, 1);
	StandupApplication::getInstance()->getRoot()->addFrameListener(clockVis);

	//Create ogre texture
	Ogre::TexturePtr tex = StandupApplication::getInstance()->getRoot()->getTextureManager()->createManual(
		"RTT",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		800,
		600,
		0,
		Ogre::PF_PVRTC_RGBA4,
		Ogre::TU_RENDERTARGET);

	mOgreRenderTexture = tex->getBuffer()->getRenderTarget();
	mOgreRenderTexture->setAutoUpdated(false);
	//mOgreRenderTexture->setActive(false);

	//create Cam
	mRTTCam = mSceneMgr->createCamera("RTTCam");
	mRTTCam->setPosition(-100, 0, 0);
	mRTTCam->lookAt(Ogre::Vector3(0,0,0));
	mRTTCam->setNearClipDistance(1);

	//create Viewport
	mRTTViewport = mOgreRenderTexture->addViewport(mRTTCam);
	mRTTViewport->setOverlaysEnabled(true);
	mRTTViewport->setClearEveryFrame(true);
	mRTTViewport->setBackgroundColour(Ogre::ColourValue(0,0,0,0));

	return tex;
}



/************************************************************************/
/* ------------------------------Dialog 3 - RIGHT-----------------------*/
/************************************************************************/
void GUI::createDialog3( WindowManager &wmgr )
{
	mDialogWindow3 = static_cast<FrameWindow*>(wmgr.createWindow( "OgreTray/FrameWindow", "Dialog 3" ));
	mDialogWindow3->setPosition( mDialogWindow1->getPosition() + UVector2( UDim( 1.0f, 0 ), UDim(0, 0 ) ) );
	mDialogWindow3->setSize( UVector2( UDim( 1.0f, 0 ), UDim( 1.0f, 0 ) ) );
	mDialogWindow3->setSizingEnabled(false);
	mDialogWindow3->setTitleBarEnabled(false);
	mDialogWindow3->setDragMovingEnabled(false);
	mDialogWindow3->setText( "Video Settings" );
	mDialogWindow3->setFrameEnabled(false);
	mDialogWindow3->setAlpha(0);
	mDialogWindow3->setProperty("YRotation","90.0");
	mWindowRoot->addChildWindow( mDialogWindow3 );

	// dialog3ButtonLeft
	mDialog3ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "Dialog 1/QuitButton3"));
	mDialog3ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	mDialog3ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.0f, 0 ) ) );
	mDialog3ButtonLeft->setAlwaysOnTop(true);
	mDialog3ButtonLeft->setAlpha(0);
	mDialog3ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog3ButtonLeftClicked,this));
	mDialog3ButtonLeft->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&GUI::dialog3ButtonLeftHoverIn,this));
	mDialog3ButtonLeft->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea,CEGUI::Event::Subscriber(&GUI::dialog3ButtonLeftHoverOut,this));
	mDialogWindow3->addChildWindow(mDialog3ButtonLeft);
	mDialog3ButtonLeft->setInheritsAlpha(false);

	Ogre::TexturePtr tex = createCEGUI_RTTScene();
	//Create cegui texture
	CEGUI::Texture &guiTex = StandupApplication::getInstance()->getOgreCEGUIRenderer()->createTexture(tex);

	//IMAGESET
	CEGUI::Imageset &imageSet =
		CEGUI::ImagesetManager::getSingleton().create("RTTImageset", guiTex);
	imageSet.defineImage("RTTImage",
		CEGUI::Point(0.0f, 0.0f),
		CEGUI::Size(guiTex.getSize().d_width,
		guiTex.getSize().d_height),
		CEGUI::Point(0.0f, 0.0f));

	//create Window
	Window *dialog3VideoWindow = wmgr.createWindow("OgreTray/StaticImage", "RTTWindow");
	dialog3VideoWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.9f, 0), CEGUI::UDim(0.65f, 0)));
	dialog3VideoWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.50f, 0)));
	dialog3VideoWindow->setProperty("FrameEnabled", "False");
	dialog3VideoWindow->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));
	dialog3VideoWindow->setInheritsAlpha(false);
	mDialogWindow3->addChildWindow(dialog3VideoWindow);
}



/************************************************************************/
/* ------------------------------Dialog 2 - LEFT------------------------*/
/************************************************************************/
void GUI::createDialog2( WindowManager &wmgr )
{
	mDialogWindow2 = static_cast<FrameWindow*>(wmgr.createWindow( "OgreTray/FrameWindow", "mDialogWindow2" ));
	mDialogWindow2->setPosition(mDialogWindow1->getPosition() +  UVector2(UDim( -1.0f, 0 ), UDim(0, 0 )));
	// set size to be half the size of the parent
	mDialogWindow2->setSize( UVector2( UDim( 1.f, 0 ), UDim( 1.0f, 0 ) ) );
	mDialogWindow2->setSizingEnabled(false);
	mDialogWindow2->setTitleBarEnabled(false);
	mDialogWindow2->setDragMovingEnabled(false);
	mDialogWindow2->setFrameEnabled(false);
	mDialogWindow2->setAlpha(0);
	mDialogWindow2->setText( "Wakeup Time" );
	mDialogWindow2->setProperty("YRotation","-90.0");
	mWindowRoot->addChildWindow( mDialogWindow2 );	



	// dialog2ButtonRight -> switch to Dialog 1
	mDialog2ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog2ButtonRight"));
	mDialog2ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	mDialog2ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.0f, 0 ) ) );
	mDialog2ButtonRight->setAlwaysOnTop(true);
	mDialog2ButtonRight->setAlpha(0);
	mDialog2ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog2ButtonRightClicked,this));
	mDialog2ButtonRight->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&GUI::dialog2ButtonRightHoverIn,this));
	mDialog2ButtonRight->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea,CEGUI::Event::Subscriber(&GUI::dialog2ButtonRightHoverOut,this));
	mDialog2ButtonRight->setInheritsAlpha(false);

	mDialogWindow2->addChildWindow(mDialog2ButtonRight);


	//mDialog2Slider -> set the Wackup Time
	mDialog2Slider = static_cast<Slider*>(wmgr.createWindow("OgreTray/Slider", "mDialog2Slider"));
	mDialog2Slider->setPosition(UVector2(UDim(0.2f,0), UDim(0.7f,0)));
	mDialog2Slider->setSize(UVector2(UDim(0.6f,0), UDim(0.02f,0)));
	mDialog2Slider->setAlwaysOnTop(true);
	mDialog2Slider->setInheritsAlpha(false);
	mDialog2Slider->setMaxValue(0.9999f);
	mDialog2Slider->setCurrentValue(0.5f);
	//mDialog2Slider->subscribeEvent(CEGUI::Scrollbar::EventScrollPositionChanged,CEGUI::Event::Subscriber(&GUI::scrollPositionChanged, this));
	mDialogWindow2->addChildWindow(mDialog2Slider);


	//staticText AlarmTime
	mDialog2AlarmTime = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2AlarmTime"));
	mDialogWindow2->addChildWindow(mDialog2AlarmTime);
	mDialog2AlarmTime->setSize(UVector2(UDim(0.1f, 0), UDim(0.05f,0)));
	mDialog2AlarmTime->setPosition(UVector2(UDim(0.15f,0), UDim(0.6f,0)));	
	mDialog2AlarmTime->setProperty("FrameEnabled", "False");
	//	mDialog2AlarmTime->setFont((CEGUI::utf8*)"Comic_12");
	mDialog2AlarmTime->setProperty("HorzFormatting", "HorzCentred");
	mDialog2AlarmTime->setProperty("VertFormatting", "VertCentred");
	mDialog2AlarmTime->setProperty("BackgroundEnabled","False");
	mDialog2AlarmTime->setInheritsAlpha(false);
	//mDialog2AlarmTime->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::swiftLeft,this));


	//mDialog2Checkbox -> aktivate Alarm Clock
	mDialog2Checkbox = static_cast<Checkbox*>(wmgr.createWindow("OgreTray/Checkbox", "mDialog2Checkbox"));
	mDialog2Checkbox->setSelected( false );
	mDialog2Checkbox->setPosition(UVector2(UDim (0.02f,0), UDim(0.7f,0)));
	mDialog2Checkbox->setSize(UVector2(UDim(0.11f, 0), UDim(0.11f, 0)));
	bool valueCheckbox = mDialog2Checkbox->isSelected(); // Retrieve whether it is checked
	mDialogWindow2->addChildWindow(mDialog2Checkbox);
	mDialog2Checkbox->setInheritsAlpha(false);
	mDialog2Checkbox->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged,CEGUI::Event::Subscriber(&GUI::checkBoxClicked,this));
	
	//staticText mDialog2Clock
	mDialog2Clock = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2Clock"));
	mDialogWindow2->addChildWindow(mDialog2Clock);
	mDialog2Clock->setSize(UVector2(UDim(0.1f, 0), UDim(0.05f,0)));
	mDialog2Clock->setProperty("FrameEnabled", "False");
	mDialog2Clock->setProperty("BackgroundEnabled","False");
	mDialog2Clock->setProperty("Font","Comic_12");
	mDialog2Clock->setProperty("HorzFormatting", "HorzCentred");
	mDialog2Clock->setProperty("VertFormatting", "VertCentred");
	mDialog2Clock->setInheritsAlpha(false);

	
	//staticText mDialog2StateInfo
	mDialog2StateInfo = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2StateInfo"));
	mDialogWindow2->addChildWindow(mDialog2StateInfo);
	mDialog2StateInfo->setSize(UVector2(UDim(1.0f, 0), UDim(0.05f,0)));
	mDialog2StateInfo->setPosition(UVector2(UDim(0,0),UDim(0.90f,0)));
	mDialog2StateInfo->setProperty("FrameEnabled", "False");
	mDialog2StateInfo->setProperty("BackgroundEnabled","False");
	mDialog2StateInfo->setProperty("Font","Comic_16");
	mDialog2StateInfo->setProperty("HorzFormatting", "HorzCentred");
	mDialog2StateInfo->setProperty("VertFormatting", "VertCentred");
	mDialog2StateInfo->setInheritsAlpha(false);
	mDialog2StateInfo->setText("Please choose wakeup time and press activate.");


	//staticText mDialog2CurrentTime
	mDialog2CurrentTime = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2CurrentTime"));
	mDialogWindow2->addChildWindow(mDialog2CurrentTime);
	mDialog2CurrentTime->setProperty("FrameEnabled", "False");
	mDialog2CurrentTime->setProperty("Font","Comic_12");
	mDialog2CurrentTime->setAlpha(0.8f);
	mDialog2CurrentTime->setProperty("HorzFormatting", "HorzCentred");
	mDialog2CurrentTime->setProperty("VertFormatting", "VertCentred");
	mDialog2CurrentTime->setInheritsAlpha(false);
	//staticText mDialog2CurrentTimeHelper
	mDialog2CurrentTimeHelper = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2CurrentTimeHelper"));
	mDialogWindow2->addChildWindow(mDialog2CurrentTimeHelper);
	mDialog2CurrentTimeHelper->setPosition(UVector2(UDim(0.205f,0), UDim(0.71f,0)));	
	mDialog2CurrentTimeHelper->setProperty("FrameEnabled", "False");
	mDialog2CurrentTimeHelper->setProperty("Font","Comic_12");
	mDialog2CurrentTimeHelper->setProperty("HorzFormatting", "HorzCentred");
	mDialog2CurrentTimeHelper->setProperty("VertFormatting", "VertCentred");
	mDialog2CurrentTime->setAlpha(0.8f);
	mDialog2CurrentTimeHelper->setInheritsAlpha(false);
}

/************************************************************************/
/* ------------------------------Dialog 1 - CENTER----------------------*/
/************************************************************************/
void GUI::createDialog1( WindowManager &wmgr )
{
	mDialogWindow1 = static_cast<FrameWindow*>(wmgr.createWindow( "OgreTray/FrameWindow", "mDialogWindow1" ));
	mDialogWindow1->setPosition( UVector2( UDim( 0, 0 ), UDim( 0, 0 ) ) );
	mDialogWindow1->setSize( UVector2( UDim( 1.0f, 0 ), UDim( 1.0f, 0 ) ) );
	mDialogWindow1->setSizingEnabled(false);
	mDialogWindow1->setTitleBarEnabled(false);
	mDialogWindow1->setDragMovingEnabled(false);
	mDialogWindow1->setFrameEnabled(false);
	mDialogWindow1->setAlpha(0);
	mDialogWindow1->setProperty("YRotation","0.0");
	mDialogWindow1->setText( "Dialog 1" );

	
	mWindowRoot->addChildWindow( mDialogWindow1 );


	// dialog1ButtonRight
	mDialog1ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonRight"));
	mDialog1ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	mDialog1ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.0f, 0 ) ) );
	mDialog1ButtonRight->setAlwaysOnTop(true);
	mDialog1ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonRightClicked,this));
	mDialogWindow1->addChildWindow(mDialog1ButtonRight);
	mDialog1ButtonRight->setAlpha(0);
	mDialog1ButtonRight->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&GUI::dialog1ButtonRightHoverIn,this));
	mDialog1ButtonRight->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea,CEGUI::Event::Subscriber(&GUI::dialog1ButtonRightHoverOut,this));
	mDialog1ButtonRight->setInheritsAlpha(false);

	// dialog1ButtonLeft
	mDialog1ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonLeft"));
	mDialog1ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	mDialog1ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.0f, 0 ) ) );
	mDialog1ButtonLeft->setAlwaysOnTop(true);
	mDialog1ButtonLeft->setAlpha(0);
	mDialog1ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonLeftClicked,this));
	mDialogWindow1->addChildWindow(mDialog1ButtonLeft);
	mDialog1ButtonLeft->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&GUI::dialog1ButtonLeftHoverIn,this));
	mDialog1ButtonLeft->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea,CEGUI::Event::Subscriber(&GUI::dialog1ButtonLeftHoverOut,this));
	mDialog1ButtonLeft->setInheritsAlpha(false);
}


