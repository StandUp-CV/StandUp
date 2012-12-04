/*
-----------------------------------------------------------------------------
Filename:    BaseView.cpp
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
*/
#include "stdafx.h"
#include "BaseView.h"

//-------------------------------------------------------------------------------------
BaseView::BaseView(Ogre::Root *root, Ogre::String &instanceName)
{

	mInstanceName=instanceName;	// ?? wird Inhalt kopiert?? 

	mRoot=root;

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mCamera = mSceneMgr->createCamera("ViewCam");

	mRenderTarget = 0;
}

void BaseView::setupViewport(void)
{
	mViewport = mRenderTarget->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	mCamera->setAspectRatio(
		Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
}

//-------------------------------------------------------------------------------------
BaseView::~BaseView(void)
{
}

Ogre::RenderTarget& BaseView::getRenderTarget(){
	return *mRenderTarget;
}

//-------------------------------------------------------------------------------------

	//Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Node1");
	//node->attachObject(entity);

    // create your scene here :)




