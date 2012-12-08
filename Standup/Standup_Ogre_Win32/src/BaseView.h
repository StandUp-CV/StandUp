/*
-----------------------------------------------------------------------------
Filename:    BaseView.h
-----------------------------------------------------------------------------
*/
#ifndef __BaseView_h_
#define __BaseView_h_

#include "stdafx.h"
#include "BaseApplication.h"

class BaseView
{

public:
	BaseView( Ogre::Root* root, Ogre::String &instanceName );
	virtual ~BaseView(void);
	
	void BaseView::setupViewport(int i);
	virtual void setupRenderTarget(void) = 0;  
	virtual void createScene(void) = 0;
	virtual Ogre::RenderTarget& getRenderTarget();
	virtual void update() {};
	

protected:

	Ogre::String mInstanceName;

	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderTarget *mRenderTarget;
	Ogre::Viewport* mViewport;

};

#endif // #ifndef __BaseView_h_
