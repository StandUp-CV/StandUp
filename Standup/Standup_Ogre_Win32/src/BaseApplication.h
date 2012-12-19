/// \file src\BaseApplication.h
///
/// \brief Declares the base application class.

/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
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
-----------------------------------------------------------------------------
*/
#ifndef __BaseApplication_h_

/// \def __BaseApplication_h_();
///
/// \brief A macro that defines base application h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define __BaseApplication_h_

#include "stdafx.h"
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>



#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "AnimationBuilder.h"
#include "CameraTest.h"
#include "GUI.h"


#define CUBEFACE_SIZE 1024

class ViewManager;

/// \class BaseApplication
///
/// \brief Base application.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:

    /// \fn BaseApplication::BaseApplication(void);
    ///
    /// \brief Default constructor.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    BaseApplication(void);

    /// \fn virtual BaseApplication::~BaseApplication(void);
    ///
    /// \brief Destructor.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual ~BaseApplication(void);

    /// \fn virtual void BaseApplication::go(void);
    ///
    /// \brief Goes this BaseApplication.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void go(void);
	// get the Ogre Renderer
	virtual CEGUI::OgreRenderer* getOgreCEGUIRenderer();
	// get the Ogre3D root node
	virtual Ogre::Root* getRoot(void);
protected:

    /// \fn virtual bool BaseApplication::setup();
    ///
    /// \brief basic instatiation of ogre.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool setup();

	/// \fn virtual bool BaseApplication::configure(void);
	///
	/// \brief Configures this BaseApplication.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return true if it succeeds, false if it fails.

	virtual bool configure(void);

    /// \fn virtual void BaseApplication::chooseSceneManager(void);
    ///
    /// \brief Choose scene manager.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void chooseSceneManager(void);

    /// \fn virtual void BaseApplication::createCamera(void);
    ///
    /// \brief Creates the camera.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void createCamera(void);

    /// \fn virtual void BaseApplication::createFrameListener(void);
    ///
    /// \brief Creates frame listener.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void createFrameListener(void);

    /// \fn virtual void BaseApplication::createScene(void) = 0;
    ///
    /// \brief Creates the scene.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void createScene(void) = 0; // Override me!

    /// \fn virtual void BaseApplication::destroyScene(void);
    ///
    /// \brief Destroys the scene.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void destroyScene(void);

    /// \fn virtual void BaseApplication::createViewports(void) = 0;
    ///
    /// \brief Creates the viewports.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void createViewports(void) = 0;

    /// \fn virtual void BaseApplication::setupResources(void);
    ///
    /// \brief Sets up the resources.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void setupResources(void);

    /// \fn virtual void BaseApplication::createResourceListener(void);
    ///
    /// \brief Creates resource listener.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void createResourceListener(void);

    /// \fn virtual void BaseApplication::loadResources(void);
    ///
    /// \brief Loads the resources.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012

    virtual void loadResources(void);

	/// \fn CEGUI::MouseButton BaseApplication::convertButton(OIS::MouseButtonID buttonID);
	///
	/// \brief CEGUI convertButton.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param buttonID
	/// Identifier for the button.
	///
	/// \return The button converted.

	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    /// \fn virtual bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt);
    ///
    /// \brief Ogre::FrameListener.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param evt
    /// The event.
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    /// \fn virtual bool BaseApplication::keyPressed( const OIS::KeyEvent &arg );
    ///
    /// \brief OIS::KeyListener.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param arg
    /// The argument.
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool keyPressed( const OIS::KeyEvent &arg );

    /// \fn virtual bool BaseApplication::keyReleased( const OIS::KeyEvent &arg );
    ///
    /// \brief Key released.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param arg
    /// The argument.
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool keyReleased( const OIS::KeyEvent &arg );

    /// \fn virtual bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg );
    ///
    /// \brief OIS::MouseListener.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param arg
    /// The argument.
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool mouseMoved( const OIS::MouseEvent &arg );

    /// \fn virtual bool BaseApplication::mousePressed( const OIS::MouseEvent &arg,
    /// OIS::MouseButtonID id );
    ///
    /// \brief Mouse pressed.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param arg
    /// The argument.
    /// \param id
    /// The identifier.
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    /// \fn virtual bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg,
    /// OIS::MouseButtonID id );
    ///
    /// \brief Mouse released.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param arg
    /// The argument.
    /// \param id
    /// The identifier.
    ///
    /// \return true if it succeeds, false if it fails.

    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    /// \fn virtual void BaseApplication::windowResized(Ogre::RenderWindow* rw);
    ///
    /// \brief Ogre::WindowEventListener Adjust mouse clipping area.
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param [in,out] rw
    /// If non-null, the rw.

    virtual void windowResized(Ogre::RenderWindow* rw);

    /// \fn virtual void BaseApplication::windowClosed(Ogre::RenderWindow* rw);
    ///
    /// \brief Unattach OIS before window shutdown (very important under Linux)
    ///
    /// \author Hans Ferchland
    /// \date 19.12.2012
    ///
    /// \param [in,out] rw
    /// If non-null, the rw.

    virtual void windowClosed(Ogre::RenderWindow* rw);

	/// \fn virtual void BaseApplication::createCEGUI();
	///
	/// \brief creates the base components of Crazy Eddie GUI.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	virtual void createCEGUI();

    Ogre::Root *mRoot;  /*!< The root */
    Ogre::Camera* mCamera;  /*!< The camera */
    Ogre::SceneManager* mSceneMgr;  /*!< Manager for scene */
    Ogre::RenderWindow* mWindow;	/*!< The window */
	Ogre::Viewport* mWindowViewport;	/*!< The window viewport */
    Ogre::String mResourcesCfg; /*!< The resources configuration */
    Ogre::String mPluginsCfg;   /*!< The plugins configuration */
	//CEGUI Fields
	CEGUI::OgreRenderer* mOgreCEGUIRenderer;	/*!< The ogre cegui renderer */
	CEGUI::System* mCEGUISystem;	/*!< The cegui system */
    bool mCursorWasVisible; /*!< true to show, false to hide the cursor was */
    bool mShutDown; /*!< true to shut down */

    //OIS Input devices
    OIS::InputManager* mInputManager;   /*!< Manager for input */
    OIS::Mouse*    mMouse;  /*!< The mouse */
    OIS::Keyboard* mKeyboard;   /*!< The keyboard */
	// saves the inital cam pos so you can reset with F3
	Ogre::Vector3* mDefaultCamPosition; /*!< The default camera position */
	// the refernce to the mGUI resposible class
    GUI* mGUI;  /*!< The graphical user interface */
};

#endif // #ifndef __BaseApplication_h_
