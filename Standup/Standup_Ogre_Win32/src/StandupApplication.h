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

class StandupApplication : public BaseApplication
{
public:
    StandupApplication(void);
    virtual ~StandupApplication(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	bool configure();
};

#endif // #ifndef __StandupApplication_h_
