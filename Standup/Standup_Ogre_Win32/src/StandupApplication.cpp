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
#include "ClockVisualization.h"


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
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));    
}

/*
 *	create Camera
 */
void StandupApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam"); 
	mCamera->setPosition(*mDefaultCamPosition);
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(1);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);	
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
	//Ogre::Light* spotLight = mSceneMgr->createLight(name);
	//spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	//spotLight->setDiffuseColour(1.0, 1.0, 1.0);
	//spotLight->setSpecularColour(1.0, 1.0, 1.0);
	//spotLight->setDirection(-xPos/xPos, -1, -zPos/zPos);
	//spotLight->setPosition(xPos, 250.0, zPos);
	//spotLight->setAttenuation(500.0f, 1.0f, 0.007f, 0.0f);
	//spotLight->setSpotlightRange(Ogre::Degree(180), Ogre::Degree(180));

	Ogre::Light* light1 = mSceneMgr->createLight("Light1");
	light1->setType(Ogre::Light::LT_POINT);
	light1->setPosition(20,0,0);
}

/*
 *	create Scene
 */
void StandupApplication::createScene(void)
{
	// Create a skybox
	/*mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	// set lights
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// create Nodes 
	mClockNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ClockNode");
	mView1 = mClockNode->createChildSceneNode("View1");
	mView2 = mClockNode->createChildSceneNode("View2");
	mView3 = mClockNode->createChildSceneNode("View3");


	//TutorialApplication::createLightBillboards();

	// create a billboardset
	Ogre::Entity* plane1 =  mSceneMgr->createEntity(Ogre::SceneManager::PT_PLANE);
	plane1->setMaterialName("Examples/BumpyMetal");
	
	 	// create Ground Entity and Material
	 	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	 	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	 		plane, 200, 200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	 	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	 	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	 	entGround->setMaterialName("Examples/BumpyMetal");
	 	// entGround->setCastShadows(false);
		mView2->attachObject( plane1 );
*/
	// create lights for the scene
	createLights();

	// create Ground Entity and Material, Enable Shadows
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 200, 200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	groundNode->attachObject(entGround);
	groundNode->setPosition(-50,-30,0);
	entGround->setMaterialName("Examples/BumpyMetal");
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Create a skybox
	mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	// set lights
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	// Create clock
	Clock clock = Clock();
	ClockVisualization* clockVis = new ClockVisualization("Clock", mSceneMgr, &clock);
	mRoot->addFrameListener(clockVis);
	
	// CEGUI
	WindowManager& wmgr = WindowManager::getSingleton();

	Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().setGUISheet( myRoot );

	FrameWindow* fWnd = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "testWindow" ));

	myRoot->addChildWindow( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.75f, 0 ), UDim( 0.75f, 0 ) ) );
	// set size to be half the size of the parent
	fWnd->setSize( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
	fWnd->setText( "Hello World!" );

	CEGUI::Window *quit = wmgr.createWindow("OgreTray/Button", "testWindow/QuitButton");
	quit->setText("Quit");
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.1, 0)));
	quit->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.9f, 0 ) ) );
	fWnd->addChildWindow(quit);

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

/*
* createLightBillboards
*/
void StandupApplication::createLightBillboards(void)
{

	// create a billboardset
	/*Ogre::BillboardSet* lightSet1 = mSceneMgr->createBillboardSet("lightSet1");
	lightSet1->setMaterialName("Examples/FlyingLightMaterial");

	// create billboards
	// Red light billboard, in "off" state
	Ogre::Vector3 redLightPosition(74, -8, -70);
	Ogre::Billboard* mRedLightBoard = lightSet1->createBillboard(redLightPosition);
	mRedLightBoard->setColour(Ogre::ColourValue::Green);

	// Blue light billboard, in "off" state
	Ogre::Vector3 blueLightPosition(-87, -8, -70);
	Ogre::Billboard* mBlueLightBoard = lightSet1->createBillboard(blueLightPosition);
	mBlueLightBoard->setColour(Ogre::ColourValue::Red);

	// White light billboard, in "off" state
	Ogre::Vector3 whiteLightPosition(-5.5, 30, -80);
	Ogre::Billboard* mWhiteLightBoard = lightSet1->createBillboard(whiteLightPosition);
	mWhiteLightBoard->setColour(Ogre::ColourValue::Blue);


	// Red light, in "off" state
	Ogre::Light* mRedLight = mSceneMgr->createLight("RedFlyingLight");
	mRedLight->setType(Ogre::Light::LT_POINT);
	mRedLight->setPosition(redLightPosition);
	mRedLight->setDiffuseColour(Ogre::ColourValue::White);
	mView1->attachObject(mRedLight);

	// Blue light, in "off" state
	Ogre::Light* mBlueLight = mSceneMgr->createLight("BlueFlyingLight");
	mBlueLight->setType(Ogre::Light::LT_POINT);
	mBlueLight->setPosition(blueLightPosition);
	mBlueLight->setDiffuseColour(Ogre::ColourValue::White);
	mView1->attachObject(mBlueLight);

	// White light in "off" state
	Ogre::Light*mWhiteLight = mSceneMgr->createLight("WhiteFlyingLight");
	mWhiteLight->setType(Ogre::Light::LT_POINT);
	mWhiteLight->setPosition(whiteLightPosition);
	mWhiteLight->setDiffuseColour(Ogre::ColourValue::White);
	mView1->attachObject(mWhiteLight);

	// attachObject to Nodes
	mView1->attachObject( lightSet1 );*/
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
