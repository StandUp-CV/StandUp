
#ifndef __ClockView_h_
#define __ClockView_h_

#include "stdafx.h"
#include "RTTView.h"


class ClockView : public RTTView
{
public:

	ClockView (Ogre::Root *root, Ogre::String &instanceName) : RTTView(root,instanceName){}

protected:
	virtual void createScene();
};

#endif
