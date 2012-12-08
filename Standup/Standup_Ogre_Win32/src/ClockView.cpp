#include "stdafx.h"
#include "ClockView.h"

using namespace CEGUI;

void ClockView::createScene()
{
	Ogre::Entity* clockEntity = mSceneMgr->createEntity("entity1", "ogrehead.mesh");
	//mSceneMgr->getRootSceneNode()->attachObject(clockEntity);
	//// Position it at 500 in Z direction
	//mCamera->setPosition(Ogre::Vector3(0,0,80));
	//// Look back along -Z
	//mCamera->lookAt(Ogre::Vector3(0,0,-300));
	//mCamera->setNearClipDistance(5);

	
	//CEGUI::OgreRenderer &or = CEGUI::OgreRenderer->create(*mRenderTarget);

	//CEGUI::RenderingRoot *rr = new CEGUI::RenderingRoot();

	WindowManager& wmgr = WindowManager::getSingleton();

	Window* sheet = wmgr.createWindow( "DefaultWindow", mInstanceName + "root" );
	System::getSingleton().setGUISheet( sheet );

	//sheet->setRenderingSurface(mRs);


	Window *si = wmgr.createWindow("OgreTray/Button", mInstanceName + "RTTWindow");
	si->setSize(CEGUI::UVector2(UDim(1.0f, 0),
		UDim(1.0f, 0)));
	si->setPosition(CEGUI::UVector2(UDim(0.1f, 0),
		UDim(0.0f, 0)));

	//si->setProperty(mInstanceName + "Image", PropertyHelper::imageToString(&imageSet.getImage(mInstanceName + "_RTTImage")));	

	sheet->addChildWindow( si );

	// position a quarter of the way in from the top-left of parent.
	//fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
	//// set size to be half the size of the parent
	//fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );
	//fWnd->setText( "Hello World!" );
	//fWnd->setUsingAutoRenderingSurface(true);

	//CEGUI::Window *quit = wmgr.createWindow("OgreTray/Button", this->mInstanceName +"testWindow/QuitButton");
	//quit->setText("Quit");
	//quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.1, 0)));
	//quit->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.9f, 0 ) ) );
	//fWnd->addChildWindow(quit);




	//CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	//CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	//CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
	//quit->setText("Quit");
	//quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

	//sheet->addChildWindow(quit);
	//CEGUI::System::getSingleton().setGUISheet(sheet);

}

