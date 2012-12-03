

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

const BaseView** ViewManager::getViews() const
{
	return (const BaseView**) mViews;
}

void ViewManager::update() const
{
	for (int i=0;i<4;i++) mViews[i]->update();
}