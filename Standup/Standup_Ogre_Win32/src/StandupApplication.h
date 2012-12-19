/*
-----------------------------------------------------------------------------
Filename:    StandupApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/

	  Modified by Hans Ferchland, Roman Hillebrand and Hady Khalifa
	  during Project for Computergraphic.
-----------------------------------------------------------------------------
*/
#ifndef __StandupApplication_h_
#define __StandupApplication_h_

#include "stdafx.h"
#include "BaseApplication.h"
#include <OgrePrerequisites.h>

using namespace CEGUI;
//! StandupApplication class is the core of Standup.
/*!
	This class extends the BaseApplication and implements 
	content and behaviour.
 */
class StandupApplication : public BaseApplication
{
public:

	//! Gets the one and only pointer to the StandupApplication.    
	/*! 
		Creates the application if not instatiated already. 
		Returns the refernce if it is there.
		\return the pointer to the one and only StandupApplication.   
	*/
	static StandupApplication* getInstance();
	//! Gets the mouse pointer of the ogre application.    
	/*!     
		\return the pointer to the ogre mouse      
		\sa Ogre::Mouse    
	*/
	OIS::Mouse* getMouse() { return mMouse; }
	//! Gets the keyboard pointer of the ogre application.    
	/*!     
		\return the pointer to the ogre keyboard      
		\sa Ogre::Keyboard    
	*/
	OIS::Keyboard* getKeyboard() { return mKeyboard; }
	//! Creates the CEGUI components and the applications main gui-content    
	/*!     
		\sa BaseApplication.createCEGUI(), GUI, CEGUI   
	*/
	void createCEGUI() override {
		BaseApplication::createCEGUI();
		// CEGUI
		mGUI = new GUI(mCEGUISystem, mRoot);
		mRoot->addFrameListener(mGUI);
		mGUI->createScene();

	}
	//! Gets the root of the ogre application.    
	/*!     
		\return the pointer to the ogre root      
		\sa Ogre::Root    
	*/
	Ogre::Root* getRoot(void) {
		return mRoot;
	}
protected:
	bool configure(); /*!< Configures the options window and window title */
	virtual void createViewports(void); /*!< Creates the applications viewport */
	virtual void createCamera(void); /*!< Creates the camera for the applications */
	virtual void createScene(void); /*!< Creates the initial scene for the application */
	void createLights(); /*!< Deprecated - Creates the lights of the scene */
	AlarmClock *mAlarmClock; /*!< References the alarm clock for the system */
private:
	StandupApplication(void); /*!< Hidden Constructor due singleton pattern. */
	static StandupApplication* instance; /*!< Instance of the one and only instance of the application */  
	virtual ~StandupApplication(void); /*!< Destructor of the Application is hidden due singleton */  
};

#endif // #ifndef __StandupApplication_h_
