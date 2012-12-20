/// \file src\StandupApplication.h
///
/// This source file is part of the
///	   ___                 __    __ _ _    _
///	  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
///	 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/// / \_// (_| | | |  __/  \  /\  /| |   <| |
/// \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
///      |___/
///      Tutorial Framework
///      http://www.ogre3d.org/tikiwiki/
///
///	  Modified by Hans Ferchland, Roman Hillebrand and Hady Khalifa
///	  during Project for Computergraphic.
///
/// \brief Declares the standup application class.

#ifndef __StandupApplication_h_

#define __StandupApplication_h_

#include "stdafx.h"
#include "BaseApplication.h"

/// \namespace CEGUI
///
/// \brief Include of the CEGUI namespace for simpler usage.

using namespace CEGUI;

/// \class StandupApplication
///
/// \brief StandupApplication class is the core of Standup.
///
///	This class extends the BaseApplication and implements
///	content and behaviour.
///
/// \author Hans Ferchland
/// \date 20.12.2012
/// \sa BaseApplication

class StandupApplication : public BaseApplication
{
public:

	/// \fn static StandupApplication* StandupApplication::getInstance();
	///
	/// \brief Gets the one and only pointer to the StandupApplication.
	///	
	/// Creates the application if not instatiated already.
	///	Returns the refernce if it is there.
	///		
	/// \author Hans Ferchland
	/// \date 20.12.2012
	///
	/// \return the pointer to the one and only StandupApplication.

	static StandupApplication* getInstance();

	/// \fn OIS::Mouse* StandupApplication::getMouse()
	///
	/// \brief Gets the mouse pointer of the ogre application.  
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012
	///
	/// \return null if it fails, else the ogre3d mouse.
	///	\sa Ogre::Mouse

	OIS::Mouse* getMouse() { return mMouse; }

	/// \fn OIS::Keyboard* StandupApplication::getKeyboard()
	///
	/// \brief Gets the keyboard pointer of the ogre application.  
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012
	///
	/// \return the pointer to the ogre keyboard
	///	\sa Ogre::Keyboard

	OIS::Keyboard* getKeyboard() { return mKeyboard; }

	/// \fn void StandupApplication::createCEGUI() override
	///
	/// \brief Creates the CEGUI components and the applications main gui-content.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012
	///	\sa BaseApplication.createCEGUI(), GUI, CEGUI  

	void createCEGUI() override {
		BaseApplication::createCEGUI();
		// CEGUI
		mGUI = new GUI(mCEGUISystem, mRoot);
		mRoot->addFrameListener(mGUI);
		mGUI->createScene();

	}

	/// \fn Ogre::Root* StandupApplication::getRoot(void)
	///
	/// \brief Gets the root of the ogre application.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012
	///
	/// \return null if it fails, else the ogre3d root.

	Ogre::Root* getRoot(void) {
		return mRoot;
	}
protected:

	/// \fn bool StandupApplication::configure();
	///
	/// \brief Configures the options window and window title.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012
	///
	/// \return true if it succeeds, false if it fails.

	bool configure(); 

	/// \fn virtual void StandupApplication::createViewports(void);
	///
	/// \brief Creates the applications viewport.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012

	virtual void createViewports(void); 

	/// \fn virtual void StandupApplication::createCamera(void);
	///
	/// \brief Creates the camera for the application.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012

	virtual void createCamera(void); 

	/// \fn virtual void StandupApplication::createScene(void);
	///
	/// \brief Creates the initial scene for the application.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012

	virtual void createScene(void);

private:
	static StandupApplication* instance; /*!< Instance of the one and only instance of the application */  

	/// \fn StandupApplication::StandupApplication(void);
	///
	/// \brief Default Hidden Constructor due singleton pattern.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012

	StandupApplication(void);

	/// \fn virtual StandupApplication::~StandupApplication(void);
	///
	/// \brief Destructor of the Application is hidden due singleton.
	///
	/// \author Hans Ferchland
	/// \date 20.12.2012

	virtual ~StandupApplication(void);
};

#endif // #ifndef __StandupApplication_h_
