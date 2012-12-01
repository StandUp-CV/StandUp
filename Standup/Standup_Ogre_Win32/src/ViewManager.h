/*
-----------------------------------------------------------------------------
Filename:    ViewManager.h
-----------------------------------------------------------------------------
*/
#ifndef __ViewManager_h_
#define __ViewManager_h_

#include "stdafx.h"
#include "BaseView.h"


class ViewManager
{
private:
	BaseView* mViews[4];
public:
	ViewManager(void) { };
	void createViews(Ogre::Root* root);
	BaseView **getViews(void);

	void update();

};

#endif // #ifndef __ViewManager_h_
