/*
-----------------------------------------------------------------------------
Filename:    StandupApplication.cpp
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
#include "StandupApplication.h"
#include "ClockVisualizationCircle.h"
#include "ClockVisualizationBars.h"
#include "clock.h"

//-------------------------------------------------------------------------------------
StandupApplication* StandupApplication::instance = 0;

//-------------------------------------------------------------------------------------
StandupApplication::StandupApplication(void) : BaseApplication()
{
	
}
//-------------------------------------------------------------------------------------
StandupApplication::~StandupApplication(void)
{
}
/*
 *	create Viewports
 */
void StandupApplication::createViewports(void)
{
	// Create one viewport, entire window
	mWindowViewport = mWindow->addViewport(mCamera);
	mWindowViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	Ogre::CompositorManager::getSingleton().addCompositor(mWindowViewport, "Bloom");
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mWindowViewport, "Bloom", true);
	Ogre::CompositorManager::getSingleton().addCompositor(mWindowViewport, "HDR");
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mWindowViewport, "HDR", true);
	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(mWindowViewport->getActualWidth()) / Ogre::Real(mWindowViewport->getActualHeight()));
}

/*
 *	create Camera
 */
void StandupApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam"); 
	mCamera->setPosition(*mDefaultCamPosition);
	mCamera->setFixedYawAxis(true, Ogre::Vector3::UNIT_X);
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(1);
	mCamera->setFOVy(Ogre::Radian(Ogre::Math::PI * 0.4f));
}

/*
 *	add Spotlight

  It sets up a plain white-light spotlight pointing 
  back to the head at the designated X and Z position. 
  The spotlight is set up with a very wide range, by the line 
  spotLight->setSpotlightRange(Ogre::Degree(180), Ogre::Degree(180));.
  This is the angle of the spotlight - 180 is very wide, 
  but I did this to ensure the spotlights overlap and leave no dark spots.
  Also, the attenuation is set with 
  spotLight->setAttenuation(500.0f, 1.0f, 0.007f, 0.0f);. 
  This defines how the light weakens over distance.
 */
void StandupApplication::createLights() 
{
	//Ogre::Light* light1 = mSceneMgr->createLight("Light1");
	//light1->setType(Ogre::Light::LT_POINT);
	//light1->setPosition(5,75,0);
}

/*
 *	create Scene
 */
void StandupApplication::createScene(void)
{
	// create lights for the scene
	createLights();

	// create Ground Entity and Material, Enable Shadows
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 10000, 10000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	groundNode->attachObject(entGround);
	groundNode->setPosition(-50,-45,0);
	entGround->setMaterialName("Standup/RustySteel");
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Create a skybox
	mSceneMgr->setSkyBox(true, "Standup/TimedSkyBox");

	// set lights
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

	ClockVisualizationCircle* clockVis = new ClockVisualizationCircle(mSceneMgr, mCamera, 2);
	mRoot->addFrameListener(clockVis);
	mRoot->addFrameListener(mAlarmClock);

}

bool StandupApplication::configure() {
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(mRoot->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true, "Standup - Ogre - Win32");

		return true;
	}
	else
	{
		return false;
	}
}

StandupApplication* StandupApplication::getInstance(){
	if (instance == NULL)
		return instance = new StandupApplication();
	else
		return instance;
}

//-------------------------------------------------------------------------------------
// MAIN METHOD
//-------------------------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {

        // Create application object
        StandupApplication* app = StandupApplication::getInstance();

        try {
            app->go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
