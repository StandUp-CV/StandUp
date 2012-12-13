
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

	/************************************************************************/
	/* ------------------------------Dialog 1 - CENTER----------------------*/
	/************************************************************************/

	mDialogWindow1 = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "mDialogWindow1" ));
	mDialogWindow1->setPosition( UVector2( UDim( 0
		, 0 ), UDim( 0.70f, 0 ) ) );
	mDialogWindow1->setSize( UVector2( UDim( 1.0f, 0 ), UDim( 0.30f, 0 ) ) );
	mDialogWindow1->setSizingEnabled(false);
	mDialogWindow1->setTitleBarEnabled(false);
	mDialogWindow1->setDragMovingEnabled(false);
	mDialogWindow1->setProperty("YRotation","0.0");
	mDialogWindow1->setText( "Dialog 1" );
	mWindowRoot->addChildWindow( mDialogWindow1 );



	// dialog1ButtonRight
	PushButton* dialog1ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonRight"));
	dialog1ButtonRight->setText(">");
	dialog1ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.2f, 0)));
	dialog1ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.8f, 0 ) ) );
	dialog1ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonRightClicked,this));
	mDialogWindow1->addChildWindow(dialog1ButtonRight);


	// dialog1ButtonLeft
	PushButton* dialog1ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonLeft"));
	dialog1ButtonLeft->setText("<");
	dialog1ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.2, 0)));
	dialog1ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.8f, 0 ) ) );
	dialog1ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonLeftClicked,this));
	mDialogWindow1->addChildWindow(dialog1ButtonLeft);


	//static Text
	mDialog1TextClock = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog1TextClock"));
	mDialogWindow1->addChildWindow(mDialog1TextClock);
	mDialog1TextClock->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
	mDialog1TextClock->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0), CEGUI::UDim(0.3,0)));
	//mDialog1TextClock->setProperty("FrameEnabled", "False");
	mDialog1TextClock->setProperty("Font","Comic_12");
	mDialog1TextClock->setProperty("HorzFormatting", "HorzCentred");
	mDialog1TextClock->setProperty("VertFormatting", "VertCentred");
	//dialog1Text->setProperty("Text", "hallo");
	mDialog1TextClock->setText("");


	//static Text
	mDialog1TextAlarm = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog1TextAlarm"));
	mDialogWindow1->addChildWindow(mDialog1TextAlarm);
	mDialog1TextAlarm->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
	mDialog1TextAlarm->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0), CEGUI::UDim(0.5,0)));
	//mDialog1TextAlarm->setProperty("FrameEnabled", "False");
	mDialog1TextAlarm->setProperty("Font","Comic_12");
	mDialog1TextAlarm->setProperty("HorzFormatting", "HorzCentred");
	mDialog1TextAlarm->setProperty("VertFormatting", "VertCentred");
	//dialog1Text->setProperty("Text", "hallo");
	mDialog1TextAlarm->setText("");



	/************************************************************************/
	/* ------------------------------Dialog 2 - LEFT------------------------*/
	/************************************************************************/

	mDialogWindow2 = static_cast<FrameWindow*>(wmgr.createWindow( "OgreTray/FrameWindow", "mDialogWindow2" ));
	mDialogWindow2->setPosition(mDialogWindow1->getPosition() +  UVector2(UDim( -1.0f, 0 ), UDim( 0, 0 )));
	// set size to be half the size of the parent
	mDialogWindow2->setSize( UVector2( UDim( 1.f, 0 ), UDim( 0.30f, 0 ) ) );
	mDialogWindow2->setSizingEnabled(false);
	mDialogWindow2->setTitleBarEnabled(true);
	mDialogWindow2->setDragMovingEnabled(false);
	mDialogWindow2->setText( "Wakeup Time" );
	mDialogWindow2->setProperty("YRotation","-90.0");
	mWindowRoot->addChildWindow( mDialogWindow2 );	



	// dialog2ButtonRight -> switch to Dialog 1
	PushButton* dialog2ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog2ButtonRight"));
	dialog2ButtonRight->setText(">");
	dialog2ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.2, 0)));
	dialog2ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.8f, 0 ) ) );
	dialog2ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog2ButtonRightClicked,this));
	mDialogWindow2->addChildWindow(dialog2ButtonRight);


	//dialog2Slider -> set the Wackup Time
	dialog2Slider = static_cast<Slider*>(wmgr.createWindow("OgreTray/HorizontalScrollbar", "dialog2Slider"));
	dialog2Slider->setPosition(UVector2(UDim(0.05f,0), UDim(0.4f,0)));
	dialog2Slider->setSize(UVector2(UDim(0.9f,0), UDim(0.1f,0)));
	dialog2Slider->setProperty("DocumentSize", "101");
	dialog2Slider->setProperty("PageSize", "16");
	dialog2Slider->setProperty("StepSize", "1");
	dialog2Slider->setProperty("OverlapSize", "0");
	dialog2Slider->setProperty("ScrollPosition", "50");
	//dialog2Slider->subscribeEvent(CEGUI::Scrollbar::EventScrollPositionChanged,CEGUI::Event::Subscriber(&GUI::scrollPositionChanged, this));
	mDialogWindow2->addChildWindow(dialog2Slider);


	//staticText AlarmTime
	mDialog2AlarmTime = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2AlarmTime"));
	mDialogWindow2->addChildWindow(mDialog2AlarmTime);
	mDialog2AlarmTime->setSize(UVector2(UDim(0.1f, 0), UDim(0.3f,0)));
	mDialog2AlarmTime->setPosition(UVector2(UDim(0,0), UDim(0.2f,0)));	
	//mDialog2AlarmTime->setProperty("FrameEnabled", "False");
	//mDialog2AlarmTime->setFont((CEGUI::utf8*)"Comic_12");
	//mDialog2AlarmTime->setProperty("HorzFormatting", "HorzLeftAligned");
	//mDialog2AlarmTime->setProperty("VertFormatting", "TopAligned");
	//mDialog2AlarmTime->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::swiftLeft,this));


	//dialog2Checkbox -> aktivate Alarm Clock
	dialog2Checkbox = static_cast<Checkbox*>(wmgr.createWindow("OgreTray/Checkbox", "dialog2Checkbox"));
	dialog2Checkbox->setSelected( false );
	dialog2Checkbox->setPosition(UVector2(UDim (0,0), UDim(0.6f,0)));
	dialog2Checkbox->setSize(UVector2(UDim(0.2f, 0), UDim(0.2f, 0)));
	bool valueCheckbox = dialog2Checkbox->isSelected(); // Retrieve whether it is checked
	mDialogWindow2->addChildWindow(dialog2Checkbox);
	mDialog2AlarmTime->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged,CEGUI::Event::Subscriber(&GUI::checkBoxClicked,this));


	//staticText AlarmTime
	mDialog2ActivateText = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "mDialog2ActivateText"));
	mDialogWindow2->addChildWindow(mDialog2ActivateText);
	mDialog2ActivateText->setSize(UVector2(UDim(0.1f, 0), UDim(0.4f,0)));
	mDialog2ActivateText->setPosition(UVector2(UDim(0.3f,0), UDim(0.6f,0)));
	mDialog2ActivateText->setProperty("FrameEnabled", "False");
	mDialog2ActivateText->setProperty("Font","Comic_12");
	mDialog2ActivateText->setProperty("HorzFormatting", "HorzCentred");
	mDialog2ActivateText->setProperty("VertFormatting", "VertCentred");

	/************************************************************************/
	/* ------------------------------Dialog 3 - RIGHT-----------------------*/
	/************************************************************************/

	mDialogWindow3 = static_cast<FrameWindow*>(wmgr.createWindow( "OgreTray/FrameWindow", "Dialog 3" ));
	mDialogWindow3->setPosition( mDialogWindow1->getPosition() + UVector2( UDim( 1.0f, 0 ), UDim(-0.7f, 0 ) ) );
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
	dialog3ButtonLeft->setText("<");
	dialog3ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.077f, 0)));
	dialog3ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.9f, 0 ) ) );
	dialog3ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog3ButtonLeftClicked,this));
	mDialogWindow3->addChildWindow(dialog3ButtonLeft);

	/************************************************************************/
	/*  CREATE OGRE SCENE IN CEGUI WINDOW                                   */
	/************************************************************************/ 

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

	/************************************************************************/
	/* CREATE IMAGESET END   	                                            */
	/************************************************************************/ 





	/************************************************************************/
	/* _-----------------------ANIMATION-------------------------------------*/
	/************************************************************************/
	
	animBuilder->createAnimations(mDialogWindow1->getProperty("UnifiedXPosition"),
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
	s+= Ogre::StringConverter::toString(mCurrentMinutes) + ":";
	if(mCurrentSeconds<10)
		s+= "0";
		s+= Ogre::StringConverter::toString(mCurrentSeconds);
	return s;
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
	static float maxTime = 0;
	//update position of mDialog2AlarmTime Window
	mDialog2AlarmTime->setPosition((dialog2Slider->getThumb()->getPosition()) * (UVector2( UDim(0.9f, 0 ), UDim( 0, 0 ))));
	//update Text of mDialog2AlarmTime (example 12:34)
	mDialog2AlarmTime->setText(getSliderTimeString(static_cast<float>(dialog2Slider->getThumb()->getXPosition().asRelative(1))));
	// update 
	//mDialog2ActivateText->setText(Ogre::StringConverter::toString(dialog2Checkbox->isSelected()));
	mDialog2ActivateText->setText(Ogre::StringConverter::toString(dialog2Slider->getThumb()->getXPosition().asRelative(1)));
	
	//
	//mDialog1TextAlarm->setText(getCurrentAlarmTimeString());
	//
	mDialog1TextClock->setText(getCurrentTimeString());	

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
		Ogre::PF_R8G8B8,
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
	mRTTViewport->setOverlaysEnabled(false);
	mRTTViewport->setAutoUpdated(true);
	mRTTViewport->setClearEveryFrame(true);
	mRTTViewport->setBackgroundColour(Ogre::ColourValue(0,0,0,0));

	return tex;
}


