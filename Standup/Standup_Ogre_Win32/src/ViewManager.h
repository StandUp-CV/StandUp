/*
-----------------------------------------------------------------------------
Filename:    ViewManager.h
-----------------------------------------------------------------------------
*/
#ifndef __ViewManager_h_
#define __BViewManager_h_

#include "stdafx.h"
#include "BaseApplication.h"
#include "BaseView.h"


class ViewManager
{
private:
		BaseView* mViews[4];
public:
	ViewManager(void) { };
	void createViews(Ogre::Root* root);
	BaseView **getViews(void);

};

#endif // #ifndef __ViewManager_h_
