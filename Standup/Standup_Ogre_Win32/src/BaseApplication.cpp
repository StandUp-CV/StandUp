/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
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
#include "stdafx.h"
#include "BaseApplication.h"
#include "ViewManager.h"
#include "CubeView.h"
#include "CEGUIOgreRenderer.h"
#include "CEGUIOgreImageCodec.h"
#include "GlowMaterialListener.h"
#include "OgreResourceGroupManager.h"
#include "OgrePixelFormat.h"
#include "OgreCompositorManager.h"
#include "OgreParticleAffector.h"

//#include "alarmSound.h"

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
	mDefaultCamPosition(new Ogre::Vector3(0,45,0)),
	mOgreCEGUIRenderer(0),
	mCEGUISystem(0),
	mGUI(0),
	mWindowViewport(0)
{

}
//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;

}

//-------------------------------------------------------------------------------------
void BaseApplication::createCEGUI()
{
	// SIMPLE BOOTSTRAP
	// 
	// Bootstrap CEGUI::System with an OgreRenderer object that uses the
	// default Ogre rendering window as the default output surface, an Ogre based
	// ResourceProvider, and an Ogre based ImageCodec.
	mOgreCEGUIRenderer =
		&CEGUI::OgreRenderer::bootstrapSystem();
	// Manually control when the gui is rendered
	mOgreCEGUIRenderer->setRenderingEnabled(false);
	//Ogre::Root::getSingleton().addFrameListener(this);
	//  set the so-called default resource groups for each of 
	//  CEGUI'S resource managers
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	// select the skin
	CEGUI::SchemeManager& mSchemeManager = CEGUI::SchemeManager::getSingleton();
	mSchemeManager.create("OgreTray.scheme");
	mSchemeManager.create("WindowsLook.scheme");

	mCEGUISystem = &CEGUI::System::getSingleton();
	// Set default tooltip
	mCEGUISystem->setDefaultTooltip("OgreTray/Tooltip");
	//  set the default mouse cursor
	mCEGUISystem->setDefaultMouseCursor("WindowsLook", "MouseArrow");
}

Ogre::Root* BaseApplication::getRoot(void){
	return mRoot;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(*mDefaultCamPosition);
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    //mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller 
}
//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

//     mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
//     mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
//     mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
//     mTrayMgr->hideCursor();

    // create a params panel for displaying sample details
//     Ogre::StringVector items;
//     items.push_back("cam.pX");
//     items.push_back("cam.pY");
//     items.push_back("cam.pZ");
//     items.push_back("");
//     items.push_back("cam.oW");
//     items.push_back("cam.oX");
//     items.push_back("cam.oY");
//     items.push_back("cam.oZ");
//     items.push_back("");
//     items.push_back("Filtering");
//     items.push_back("Poly Mode");
// 
//     mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
//     mDetailsPanel->setParamValue(9, "Bilinear");
//     mDetailsPanel->setParamValue(10, "Solid");
//     mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{

	
	

	//Ogre::CompositorManager::getSingleton().addCompositor(mCamera->getViewport(), "Glow");
	//Ogre::CompositorManager::getSingleton().setCompositorEnabled(mCamera->getViewport(), "Glow", true);
	//GlowMaterialListener *gml = new GlowMaterialListener();
	//Ogre::MaterialManager::getSingleton().addListener(gml);
}
//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../media/materials/scripts/", "FileSystem");
}
//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);
	// collect and parse resources
    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();
	// create listener for mouse and keyboard
    createFrameListener();

	//////////////////////////////////////////////////////////////////////////
	//Crazy Eddie GUI Setup
	//////////////////////////////////////////////////////////////////////////
	createCEGUI();
	//////////////////////////////////////////////////////////////////////////
	//Create the Scene
	//////////////////////////////////////////////////////////////////////////
	createScene();

    return true;
};
//-------------------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	

    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	//////////////////////////////////////////////////////////////////////////
	//		CEGUI Update
	////////////////////////////////////////////////////////////////////////// 
	//Need to inject timestamps to CEGUI System.
	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    return true;
}
//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
	/*if (arg.key >= OIS::KC_1 && arg.key<=OIS::KC_3)
	{
		CubeView *cw = (CubeView*)(mViewManager->getViews()[3]);
		cw->setTargetSide(arg.key-OIS::KC_1);
	}*/

	if(arg.key == OIS::KC_F3)   // reset camera position
	{
		mCamera->setPosition(*mDefaultCamPosition);
	}

    if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

	//////////////////////////////////////////////////////////////////////////
	//		CEGUI Input Methods
	//////////////////////////////////////////////////////////////////////////
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(arg.key);
	sys.injectChar(arg.text);

    return true;
}

bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
	// CEGUI key down injection
	CEGUI::System::getSingleton().injectKeyUp(arg.key);
    return true;
}

bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	//////////////////////////////////////////////////////////////////////////
	//		CEGUI Mouse Movement Methods
	//////////////////////////////////////////////////////////////////////////
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	if (arg.state.Z.rel)
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);

    return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	// CEGUI mousePressed injection
	CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	// CEGUI mouseReleased injection
	CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    return true;
}

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

CEGUI::OgreRenderer* BaseApplication::getOgreCEGUIRenderer() {
	return mOgreCEGUIRenderer;
}

//-------------------------------------------------------------------------------------
CEGUI::MouseButton BaseApplication::convertButton(OIS::MouseButtonID buttonID)
{
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;

	default:
		return CEGUI::LeftButton;
	}
}

