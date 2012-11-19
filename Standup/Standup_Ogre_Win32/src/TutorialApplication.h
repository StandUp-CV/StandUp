/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "stdafx.h"
#include "BaseApplication.h"
#include <OgrePrerequisites.h>

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
	virtual void createViewports(void);
	virtual void createCamera(void);
	virtual void createScene(void);
	virtual void createLightBillboards(void);
	void addSpotlight(const Ogre::String name, const Ogre::Real xPos, const Ogre::Real zPos);

	 Ogre::SceneNode* mClockNode;
	 Ogre::SceneNode* mView1;
	 Ogre::SceneNode* mView2;
	 Ogre::SceneNode* mView3;

};

#endif // #ifndef __TutorialApplication_h_
