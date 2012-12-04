

/*
-----------------------------------------------------------------------------
Filename:    ViewManager.cpp
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
*/
#include "stdafx.h"
#include "ViewManager.h"
#include "CubeView.h"
#include "ClockView.h"
#include "StandupApplication.h"

void ViewManager::createViews(Ogre::Root* root)
{
	mViews[0] = new ClockView(root, Ogre::String("sideview1"));
	mViews[1] = new ClockView(root, Ogre::String("sideview2"));
	mViews[2] = new ClockView(root, Ogre::String("sideview3"));
	mViews[3] = new CubeView(root, Ogre::String("cubeview"));

	for(int i=0;i<4;i++)
	{
		mViews[i]->setupRenderTarget();
		mViews[i]->setupViewport();
		mViews[i]->createScene();
	}
}

BaseView** ViewManager::getViews(void)
{
	return mViews;
}

void ViewManager::update()
{
	for (int i=0;i<4;i++) {
		StandupApplication::getInstance()->getStandupCEGUIRenderer()->setDefaultRootRenderTarget(mViews[i]->getRenderTarget());
		mViews[i]->update();
	}
}