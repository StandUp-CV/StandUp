#include "stdafx.h"
#include "ClockView.h"

using namespace CEGUI;

void ClockView::createScene()
{
// 	Ogre::Entity* clockEntity = mSceneMgr->createEntity("entity1", "ogrehead.mesh");


	WindowManager& wmgr = WindowManager::getSingleton();

	Window* myRoot = wmgr.createWindow( "DefaultWindow", this->mInstanceName + "root" );
	System::getSingleton().setGUISheet( myRoot );

	FrameWindow* fWnd = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", this->mInstanceName +"testWindow" ));

	myRoot->addChildWindow( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
	// set size to be half the size of the parent
	fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );
	fWnd->setText( "Hello World!" );

	CEGUI::Window *quit = wmgr.createWindow("OgreTray/Button", this->mInstanceName +"testWindow/QuitButton");
	quit->setText("Quit");
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.1, 0)));
	quit->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.9f, 0 ) ) );
	fWnd->addChildWindow(quit);

	 	//mSceneMgr->getRootSceneNode()->attachObject(myRoot);
	 	//// Position it at 500 in Z direction
	 	//mCamera->setPosition(Ogre::Vector3(0,0,80));
	 	//// Look back along -Z
	 	//mCamera->lookAt(Ogre::Vector3(0,0,-300));
	 	//mCamera->setNearClipDistance(5);


	//CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	//CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	//CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
	//quit->setText("Quit");
	//quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

	//sheet->addChildWindow(quit);
	//CEGUI::System::getSingleton().setGUISheet(sheet);

}

