#include "stdafx.h"
#include "CubeView.h"

void CubeView::setupRenderTarget(void)
{
	mRenderTarget = mRoot->getAutoCreatedWindow();
}


void CubeView::createScene()
{
	Ogre::MaterialPtr renderMaterial = Ogre::MaterialManager::getSingleton().create("RttMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	renderMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	renderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("sideview1_texture");
	
	Ogre::Entity* clockEntity = mSceneMgr->createEntity("entity1", "ogrehead.mesh");
	mSceneMgr->getRootSceneNode()->attachObject(clockEntity);

	clockEntity->setMaterial(renderMaterial);

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);



}