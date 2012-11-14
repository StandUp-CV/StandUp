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

//-------------------------------------------------------------------------------------
StandupApplication::StandupApplication(void)
{
}
//-------------------------------------------------------------------------------------
StandupApplication::~StandupApplication(void)
{
}

//-------------------------------------------------------------------------------------
void StandupApplication::createCamera() {
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,50,500));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
	//BaseApplication::createCamera();
}
//-------------------------------------------------------------------------------------
void StandupApplication::createViewports() {
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / 
		Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------
void StandupApplication::createScene(void)
{
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0,0,0));
	// Create a Lights and set positions
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(0, 200.0f, 50.0f);
	light->setCastShadows(true);
	//Ogre::Light* light1 = mSceneMgr->createLight();
	//light1->setPosition(0,200,0);
	//light1->setCastShadows(false);
	//light1->setType(Ogre::Light::LightTypes::LT_SPOTLIGHT);
	//light1->setDiffuseColour(Ogre::ColourValue(1,0.75f,0.5f));

	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Create Entities
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::Entity* ogreHead2 = mSceneMgr->createEntity("Head2", "ogrehead.mesh");
	// Create plane mesh called "ground" and register it to the meshmanager
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	// Create a ground and attach it to the root node
	Ogre::Entity* entGround = mSceneMgr->createEntity(
		"GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);

	// Create a SceneNode and attach the Entity to it
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("HeadNode", Ogre::Vector3(-100,40,0));
	Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("HeadNode2", Ogre::Vector3(100,40,0));
	headNode->attachObject(ogreHead);
	headNode2->attachObject(ogreHead2);



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
        StandupApplication app;

        try {
            app.go();
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
