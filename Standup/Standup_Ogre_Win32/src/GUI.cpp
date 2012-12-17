
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
	Clock* clock;
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
	
	int hourValue = (int)(24*f);

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
	float max = 0.9846f;
	f/=max;
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
	const tm& localTime = mClock->getDisplayTime(mClock->getCurrentSecond());
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

	float max = 0.9846f;
	// get current time from clock
	const tm& localTime = mClock->getDisplayTime(mClock->getCurrentSecond());
	// get the current secs, mins and mHours
	float min = localTime.tm_min;
	float hour = localTime.tm_hour % (12 * mHourFormat); // in right time format (12 vs 24)
		float xPos = (float)(((((min/60)/24) + (hour/24)))*0.5f);
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

	//update position of mDialog2AlarmTime Window
	mDialog2AlarmTime->setPosition(((UVector2(UDim(0.15f,0),UDim(0.66f,0))) + (mDialog2Slider->getThumb()->getPosition()) * (UVector2( UDim(0.57f, 0 ), UDim( 0, 0 )))));
	mDialog2CurrentTime->setPosition((UVector2(UDim(0.2f,0),UDim(0.71f,0))) + (UVector2(UDim(getCurrentTimePosition(),0),UDim(0,0))));

	mDialog2CurrentTimeHelper->setSize( (UVector2(UDim(0,0),UDim(0.3f,0))) +(UVector2((mDialog2Slider->getThumb()->getXPosition() * UDim(0.5f,0)), UDim(0,0))));
	//update Text of mDialog2AlarmTime (example 12:34)
	mDialog2AlarmTime->setText(getSliderTimeString(static_cast<float>(mDialog2Slider->getThumb()->getXPosition().asRelative(1))));

		float max = 0.9846f;
	if(mDialog2CurrentTime->getXPosition().asRelative(1.0) <=   ((UDim(0.2f,0) +((mDialog2Slider->getThumb()->getXPosition() * UDim(0.5f,0)))).asRelative(1.0f))){
		mDialog2CurrentTimeHelper->setVisible(false);
			mDialog2CurrentTime->setSize(  (UVector2(UDim(0,0),UDim(0.3f,0))) -((UVector2(mDialog2CurrentTime->getXPosition() - UDim(0.2f,0), UDim(0,0)) - (UVector2((mDialog2Slider->getThumb()->getXPosition() * UDim(0.5f,0)), UDim(0,0))))));
	}
	else{
		mDialog2CurrentTimeHelper->setVisible(true);
			mDialog2CurrentTime->setSize(  (UVector2(UDim(0,0),UDim(0.3f,0))) -((UVector2(mDialog2CurrentTime->getXPosition() - UDim(0.2f,0), UDim(0,0)) - (UVector2((UDim(max,0) * UDim(0.5f,0)), UDim(0,0))))));
	}

	// update 
	//mDialog2CurrentTime->setText(Ogre::StringConverter::toString(mDialog2Checkbox->isSelected()));
	mDialog2CurrentTime->setText(getCurrentTimeString());
}

Ogre::TexturePtr GUI::createCEGUI_RTTScene()
{
	mSceneMgr = StandupApplication::getInstance()->getRoot()->createSceneManager(Ogre::ST_GENERIC);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	ClockVisualizationBars* clockVis = 
		new ClockVisualizationBars(mSceneMgr, mClock, 1);
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
	mDialogWindow3->setProperty("YRotation","90.0");
	mWindowRoot->addChildWindow( mDialogWindow3 );

	// dialog3ButtonLeft
	PushButton* dialog3ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "Dialog 1/QuitButton3"));
	dialog3ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	dialog3ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.0f, 0 ) ) );
	dialog3ButtonLeft->setAlwaysOnTop(true);
	dialog3ButtonLeft->setAlpha(0.2f);
	dialog3ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog3ButtonLeftClicked,this));
	mDialogWindow3->addChildWindow(dialog3ButtonLeft);


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
	dialog3VideoWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.05f, 0)));
	dialog3VideoWindow->setProperty("FrameEnabled", "False");
	dialog3VideoWindow->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));

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
	mDialogWindow2->setText( "Wakeup Time" );
	mDialogWindow2->setProperty("YRotation","-90.0");
	mWindowRoot->addChildWindow( mDialogWindow2 );	



	// dialog2ButtonRight -> switch to Dialog 1
	PushButton* dialog2ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog2ButtonRight"));
	dialog2ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	dialog2ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.0f, 0 ) ) );
	dialog2ButtonRight->setAlwaysOnTop(true);
	dialog2ButtonRight->setAlpha(0.2f);
	dialog2ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog2ButtonRightClicked,this));
	mDialogWindow2->addChildWindow(dialog2ButtonRight);


	//mDialog2Slider -> set the Wackup Time
	mDialog2Slider = static_cast<Slider*>(wmgr.createWindow("OgreTray/HorizontalScrollbar", "mDialog2Slider"));
	mDialog2Slider->setPosition(UVector2(UDim(0.2f,0), UDim(0.7f,0)));
	mDialog2Slider->setSize(UVector2(UDim(0.5f,0), UDim(0.02f,0)));
	mDialog2Slider->setProperty("DocumentSize", "101");
	mDialog2Slider->setProperty("PageSize", "16");
	mDialog2Slider->setProperty("StepSize", "1");
	mDialog2Slider->setProperty("OverlapSize", "0");
	mDialog2Slider->setProperty("ScrollPosition", "50");
	mDialog2Slider->setAlwaysOnTop(true);
	//mDialog2Slider->subscribeEvent(CEGUI::Scrollbar::EventScrollPositionChanged,CEGUI::Event::Subscriber(&GUI::scrollPositionChanged, this));
	mDialogWindow2->addChildWindow(mDialog2Slider);


	//staticText AlarmTime
	mDialog2AlarmTime = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2AlarmTime"));
	mDialogWindow2->addChildWindow(mDialog2AlarmTime);
	mDialog2AlarmTime->setSize(UVector2(UDim(0.1f, 0), UDim(0.05f,0)));
	mDialog2AlarmTime->setPosition(UVector2(UDim(0.15f,0), UDim(0.6f,0)));	
	mDialog2AlarmTime->setProperty("FrameEnabled", "False");
	//	mDialog2AlarmTime->setFont((CEGUI::utf8*)"Comic_12");
	//mDialog2AlarmTime->setProperty("HorzFormatting", "HorzLeftAligned");
	mDialog2AlarmTime->setProperty("VertFormatting", "TopAligned");
	mDialog2AlarmTime->setProperty("BackgroundEnabled","False");
	//mDialog2AlarmTime->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::swiftLeft,this));


	//mDialog2Checkbox -> aktivate Alarm Clock
	mDialog2Checkbox = static_cast<Checkbox*>(wmgr.createWindow("OgreTray/Checkbox", "mDialog2Checkbox"));
	mDialog2Checkbox->setSelected( false );
	mDialog2Checkbox->setPosition(UVector2(UDim (0,0), UDim(0.6f,0)));
	mDialog2Checkbox->setSize(UVector2(UDim(0.2f, 0), UDim(0.2f, 0)));
	bool valueCheckbox = mDialog2Checkbox->isSelected(); // Retrieve whether it is checked
	mDialogWindow2->addChildWindow(mDialog2Checkbox);
	mDialog2AlarmTime->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged,CEGUI::Event::Subscriber(&GUI::checkBoxClicked,this));


	//staticText mDialog2CurrentTime
	mDialog2CurrentTime = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2CurrentTime"));
	mDialogWindow2->addChildWindow(mDialog2CurrentTime);
	mDialog2CurrentTime->setSize(UVector2(UDim(0.2f, 0), UDim(0.3f,0)));
	mDialog2CurrentTime->setProperty("FrameEnabled", "False");
	mDialog2CurrentTime->setProperty("Font","Comic_12");
	mDialog2CurrentTime->setProperty("HorzFormatting", "HorzCentred");
	mDialog2CurrentTime->setProperty("VertFormatting", "VertCentred");
	//staticText mDialog2CurrentTimeHelper
	mDialog2CurrentTimeHelper = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2CurrentTimeHelper"));
	mDialogWindow2->addChildWindow(mDialog2CurrentTimeHelper);
	mDialog2CurrentTimeHelper->setPosition(UVector2(UDim(0.2f,0), UDim(0.71f,0)));	
	mDialog2CurrentTimeHelper->setProperty("FrameEnabled", "False");
	mDialog2CurrentTimeHelper->setProperty("Font","Comic_12");
	mDialog2CurrentTimeHelper->setProperty("HorzFormatting", "HorzCentred");
	mDialog2CurrentTimeHelper->setProperty("VertFormatting", "VertCentred");
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
	mDialogWindow1->setAlpha(0.2f);
	mDialogWindow1->setProperty("YRotation","0.0");
	mDialogWindow1->setText( "Dialog 1" );
	
	mWindowRoot->addChildWindow( mDialogWindow1 );


	// dialog1ButtonRight
	PushButton* dialog1ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonRight"));
	dialog1ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	dialog1ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.0f, 0 ) ) );
	dialog1ButtonRight->setAlwaysOnTop(true);
	dialog1ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonRightClicked,this));
	mDialogWindow1->addChildWindow(dialog1ButtonRight);


	// dialog1ButtonLeft
	PushButton* dialog1ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonLeft"));
	dialog1ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1.0f, 0)));
	dialog1ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.0f, 0 ) ) );
	dialog1ButtonLeft->setAlwaysOnTop(true);
	dialog1ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonLeftClicked,this));
	mDialogWindow1->addChildWindow(dialog1ButtonLeft);

}


