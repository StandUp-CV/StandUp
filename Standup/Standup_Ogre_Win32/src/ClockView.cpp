#include "stdafx.h"
#include "ClockView.h"


void ClockView::createScene()
{
	Ogre::Entity* clockEntity = mSceneMgr->createEntity("entity1", "ogrehead.mesh");
	mSceneMgr->getRootSceneNode()->attachObject(clockEntity);
	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);

}

