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
	const BaseView **getViews() const;		// was ist kostant? pointer oder Objekt?

	void update() const;

};

#endif // #ifndef __ViewManager_h_
