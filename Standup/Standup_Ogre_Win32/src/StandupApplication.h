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
-----------------------------------------------------------------------------
*/
#ifndef __StandupApplication_h_
#define __StandupApplication_h_

#include "stdafx.h"
#include "BaseApplication.h"
#include <OgrePrerequisites.h>

class StandupApplication : public BaseApplication
{
public:
    StandupApplication(void);
    virtual ~StandupApplication(void);

protected:
<<<<<<< HEAD:Standup/Standup_Ogre_Win32/src/StandupApplication.h
    virtual void createScene(void);
	bool configure();
=======
	virtual void createViewports(void);
	virtual void createCamera(void);
	virtual void createScene(void);
	virtual void createLightBillboards(void);
	void addSpotlight(const Ogre::String name, const Ogre::Real xPos, const Ogre::Real zPos);

	 Ogre::SceneNode* mClockNode;
	 Ogre::SceneNode* mView1;
	 Ogre::SceneNode* mView2;
	 Ogre::SceneNode* mView3;

>>>>>>> viewports:Standup/Standup_Ogre_Win32/src/TutorialApplication.h
};

#endif // #ifndef __StandupApplication_h_
