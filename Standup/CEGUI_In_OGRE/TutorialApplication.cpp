/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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
#include "TutorialApplication.h"

using namespace CEGUI;

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)

	
	WindowManager& wmgr = WindowManager::getSingleton();

	Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().setGUISheet( myRoot );

	FrameWindow* fWnd = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "testWindow" ));

	myRoot->addChildWindow( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
	// set size to be half the size of the parent
	fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );
	fWnd->setText( "Hello World!" );

	CEGUI::Window *quit = wmgr.createWindow("OgreTray/Button", "testWindow/QuitButton");
	quit->setText("Quit");
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.1, 0)));
	quit->setPosition( UVector2( UDim( 0.8f, 0 ), UDim( 0.9f, 0 ) ) );
	fWnd->addChildWindow(quit);


	//CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	//CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	//CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
	//quit->setText("Quit");
	//quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

	//sheet->addChildWindow(quit);
	//CEGUI::System::getSingleton().setGUISheet(sheet);
}



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
        TutorialApplication app;

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
