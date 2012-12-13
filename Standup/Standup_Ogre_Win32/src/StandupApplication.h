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

class StandupApplication : public BaseApplication
{
public:
    
    virtual ~StandupApplication(void);

	static StandupApplication* getInstance();
	OIS::Mouse* getMouse() { return mMouse; }
	OIS::Keyboard* getKeyboard() { return mKeyboard; }


protected:
	StandupApplication(void);
	bool configure();
	virtual void createViewports(void);
	virtual void createCamera(void);
	virtual void createScene(void);
	virtual void createLightBillboards(void);
	void createLights();
	static StandupApplication* instance;
};

#endif // #ifndef __StandupApplication_h_
