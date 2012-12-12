
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


	myRoot = wmgr.createWindow( "DefaultWindow", "myRoot" );
	System::getSingleton().setGUISheet( myRoot );



	//------------------------------Dialog 1---------------------------------------
	dialogWindow1 = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "dialogWindow1" ));
	myRoot->addChildWindow( dialogWindow1 );
	// position a quarter of the way in from the top-left of parent.
	dialogWindow1->setPosition( UVector2( UDim( 0.05f, 0 ), UDim( 0.65f, 0 ) ) );
	// set size to be half the size of the parent
	dialogWindow1->setSize( UVector2( UDim( 0.9f, 0 ), UDim( 0.30f, 0 ) ) );
	dialogWindow1->setSizingEnabled(false);
	dialogWindow1->setTitleBarEnabled(false);
	dialogWindow1->setDragMovingEnabled(false);
	dialogWindow1->setText( "Dialog 1" );

	// dialog1ButtonRight
	PushButton* dialog1ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonRight"));
	dialog1ButtonRight->setText(">");
	dialog1ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.2f, 0)));
	dialog1ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.8f, 0 ) ) );
	dialog1ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonRightClicked,this));
	dialogWindow1->addChildWindow(dialog1ButtonRight);

	// dialog1ButtonLeft
	PushButton* dialog1ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog1ButtonLeft"));
	dialog1ButtonLeft->setText("<");
	dialog1ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.2, 0)));
	dialog1ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.8f, 0 ) ) );
	dialog1ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog1ButtonLeftClicked,this));
	dialogWindow1->addChildWindow(dialog1ButtonLeft);

	//static Text
	dialog1TextClock = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "dialog1TextClock"));
	dialogWindow1->addChildWindow(dialog1TextClock);
	dialog1TextClock->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
	dialog1TextClock->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0), CEGUI::UDim(0.3,0)));
	dialog1TextClock->setProperty("FrameEnabled", "False");
	dialog1TextClock->setProperty("Font","Comic_12");
	dialog1TextClock->setProperty("HorzFormatting", "HorzCentred");
	dialog1TextClock->setProperty("VertFormatting", "VertCentred");
	//dialog1Text->setProperty("Text", "hallo");
	dialog1TextClock->setText("");
	
	//static Text
	dialog1TextAlarm = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "dialog1TextAlarm"));
	dialogWindow1->addChildWindow(dialog1TextAlarm);
	dialog1TextAlarm->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
	dialog1TextAlarm->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45, 0), CEGUI::UDim(0.5,0)));
	dialog1TextAlarm->setProperty("FrameEnabled", "False");
	dialog1TextAlarm->setProperty("Font","Comic_12");
	dialog1TextAlarm->setProperty("HorzFormatting", "HorzCentred");
	dialog1TextAlarm->setProperty("VertFormatting", "VertCentred");
	//dialog1Text->setProperty("Text", "hallo");
	dialog1TextAlarm->setText("");

	//------------------------------Dialog 2---------------------------------------
	dialogWindow2 = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "dialogWindow2" ));
	myRoot->addChildWindow( dialogWindow2 );
	// position a quarter of the way in from the top-left of parent.
	dialogWindow2->setPosition(dialogWindow1->getPosition() +  UVector2(UDim( -1.0f, 0 ), UDim( 0, 0 )));
	// set size to be half the size of the parent
	dialogWindow2->setSize( UVector2( UDim( 0.9f, 0 ), UDim( 0.30f, 0 ) ) );
	dialogWindow2->setSizingEnabled(false);
	dialogWindow2->setTitleBarEnabled(true);
	dialogWindow2->setDragMovingEnabled(false);
	dialogWindow2->setText( "Wakeup Time" );

	// dialog2ButtonRight -> switch to Dialog 1
	PushButton* dialog2ButtonRight = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "dialog2ButtonRight"));
	dialog2ButtonRight->setText(">");
	dialog2ButtonRight->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.2, 0)));
	dialog2ButtonRight->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.8f, 0 ) ) );
	dialog2ButtonRight->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog2ButtonRightClicked,this));
	dialogWindow2->addChildWindow(dialog2ButtonRight);

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

	dialogWindow2->addChildWindow(dialog2Slider);

	//staticText AlarmTime
	dialog2AlarmTime = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "dialog2AlarmTime"));
	dialogWindow2->addChildWindow(dialog2AlarmTime);
	dialog2AlarmTime->setSize(UVector2(UDim(0.1f, 0), UDim(0.3f,0)));
	dialog2AlarmTime->setPosition(UVector2(UDim(0,0), UDim(0.2f,0)));
	
	//dialog2AlarmTime->setProperty("FrameEnabled", "False");
	//dialog2AlarmTime->setFont((CEGUI::utf8*)"Comic_12");
	//dialog2AlarmTime->setProperty("HorzFormatting", "HorzLeftAligned");
	//dialog2AlarmTime->setProperty("VertFormatting", "TopAligned");
	//dialog2AlarmTime->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::swiftLeft,this));


	//dialog2Checkbox -> aktivate Alarm Clock
	dialog2Checkbox = static_cast<Checkbox*>(wmgr.createWindow("OgreTray/Checkbox", "dialog2Checkbox"));
	dialog2Checkbox->setSelected( false );
	dialog2Checkbox->setPosition(UVector2(UDim (0,0), UDim(0.6f,0)));
	dialog2Checkbox->setSize(UVector2(UDim(0.2f, 0), UDim(0.2f, 0)));
	bool valueCheckbox = dialog2Checkbox->isSelected(); // Retrieve whether it is checked
	dialogWindow2->addChildWindow(dialog2Checkbox);
	dialog2AlarmTime->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged,CEGUI::Event::Subscriber(&GUI::checkBoxClicked,this));

	//staticText AlarmTime
	dialog2ActivateText = static_cast<DefaultWindow*>(wmgr.createWindow("OgreTray/StaticText", "dialog2ActivateText"));
	dialogWindow2->addChildWindow(dialog2ActivateText);
	dialog2ActivateText->setSize(UVector2(UDim(0.1f, 0), UDim(0.4f,0)));
	dialog2ActivateText->setPosition(UVector2(UDim(0.3f,0), UDim(0.6f,0)));
	dialog2ActivateText->setProperty("FrameEnabled", "False");
	dialog2ActivateText->setProperty("Font","Comic_12");
	dialog2ActivateText->setProperty("HorzFormatting", "HorzCentred");
	dialog2ActivateText->setProperty("VertFormatting", "VertCentred");
	

	//------------------------------Dialog 3---------------------------------------
	dialogWindow3 = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "Dialog 3" ));
	myRoot->addChildWindow( dialogWindow3 );
	dialogWindow3->setPosition( dialogWindow1->getPosition() + UVector2( UDim( 1.0f, 0 ), UDim(-0.60f, 0 ) ) );
	dialogWindow3->setSize( UVector2( UDim( 0.9f, 0 ), UDim( 0.9f, 0 ) ) );
	dialogWindow3->setSizingEnabled(false);
	dialogWindow3->setTitleBarEnabled(true);
	dialogWindow3->setDragMovingEnabled(false);
	dialogWindow3->setText( "Video Settings" );

	// dialog3ButtonLeft
	PushButton* dialog3ButtonLeft = static_cast<PushButton*>(wmgr.createWindow("OgreTray/Button", "Dialog 1/QuitButton3"));
	dialog3ButtonLeft->setText("<");
	dialog3ButtonLeft->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.077f, 0)));
	dialog3ButtonLeft->setPosition( UVector2( UDim( 0, 0 ), UDim( 0.9f, 0 ) ) );
	dialog3ButtonLeft->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&GUI::dialog3ButtonLeftClicked,this));
	dialogWindow3->addChildWindow(dialog3ButtonLeft);



	/************************************************************************/
	/*  CREATE OGRE SCENE IN CEGUI WINDOW                                   */
	/************************************************************************/ 

	mSceneMgr = StandupApplication::getInstance()->getRoot()->createSceneManager(Ogre::ST_GENERIC);

	// create Entity
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	//mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	//Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	//Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -300));
	//headNode->attachObject(ogreHead);

	ClockVisualizationBars* clockVis = new ClockVisualizationBars(mSceneMgr, mClock, 1);
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
	Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();

	//create Cam
	Ogre::Camera *cam = mSceneMgr->createCamera("RTTCam");
	cam->setPosition(60, 0, -30);
	cam->lookAt(Ogre::Vector3(0,0,0));
	cam->setNearClipDistance(1);

	//create Viewport
	Ogre::Viewport *v = rtex->addViewport(cam);
	//v->setOverlaysEnabled(false);
	//v->setClearEveryFrame(true);
	v->setBackgroundColour(Ogre::ColourValue::Black);

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
	dialog3VideoWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.8f, 0), CEGUI::UDim(0.6f, 0)));
	dialog3VideoWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f, 0), CEGUI::UDim(0.2f, 0)));
	dialog3VideoWindow->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));

	dialogWindow3->addChildWindow(dialog3VideoWindow);

	/************************************************************************/
	/* CREATE IMAGESET END   	                                            */
	/************************************************************************/ 


	/************************************************************************/
	/* Animation                                                            */
	/************************************************************************/
	
	animBuilder->createAnimations(dialogWindow1->getProperty("UnifiedXPosition"), dialogWindow2->getProperty("UnifiedXPosition"), dialogWindow3->getProperty("UnifiedXPosition") );
	AnimationManager& animMng = AnimationManager::getSingleton();

	instAnim_MoveWindow1Right = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow1Right"));
	instAnim_MoveWindow1Right->setTargetWindow(dialogWindow1);

	instAnim_MoveWindow2Right= animMng.instantiateAnimation(animMng.getAnimation("MoveWindow2Right"));
	instAnim_MoveWindow2Right->setTargetWindow(dialogWindow2);

	instAnim_MoveWindow1Left = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow1Left"));
	instAnim_MoveWindow1Left->setTargetWindow(dialogWindow1);

	instAnim_MoveWindow3Left = animMng.instantiateAnimation(animMng.getAnimation("MoveWindow3Left"));
	instAnim_MoveWindow3Left->setTargetWindow(dialogWindow3);

	instAnim_moveWindow1FromRightToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow1FromRightToStart"));
	instAnim_moveWindow1FromRightToStart->setTargetWindow(dialogWindow1);

	instAnim_moveWindow2FromLeftToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow2FromLeftToStart"));
	instAnim_moveWindow2FromLeftToStart->setTargetWindow(dialogWindow2);

	instAnim_moveWindow1FromLeftToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow1FromLeftToStart"));
	instAnim_moveWindow1FromLeftToStart->setTargetWindow(dialogWindow1);

	instAnim_moveWindow3FromRightToStart = animMng.instantiateAnimation(animMng.getAnimation("moveWindow3FromRightToStart"));
	instAnim_moveWindow3FromRightToStart->setTargetWindow(dialogWindow3);

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
// return String (example 12:34) for dialog2AlarmTime CEGUI Window
String GUI::getSliderTimeString(float f){
	float max = 0.982266f;
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
	//update position of dialog2AlarmTime Window
	dialog2AlarmTime->setPosition((dialog2Slider->getThumb()->getPosition()) * (UVector2( UDim(0.9f, 0 ), UDim( 0, 0 ))));
	//update Text of dialog2AlarmTime (example 12:34)
	dialog2AlarmTime->setText(getSliderTimeString(static_cast<float>(dialog2Slider->getThumb()->getXPosition().asRelative(1))));
	// update 
	//dialog2ActivateText->setText(Ogre::StringConverter::toString(dialog2Checkbox->isSelected()));
	dialog2ActivateText->setText(Ogre::StringConverter::toString(dialog2Slider->getThumb()->getXPosition().asRelative(1)));
	
	//
	//dialog1TextAlarm->setText(getCurrentAlarmTimeString());
	//
	dialog1TextClock->setText(getCurrentTimeString());	

	return true;
}


