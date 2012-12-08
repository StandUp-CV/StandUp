#include "stdafx.h"
#include "CubeView.h"

void CubeView::setupRenderTarget(void)
{
	mRenderTarget = mRoot->getAutoCreatedWindow();
}


void CubeView::createScene()
{
	int i;

	// render texture names
	// (these are assigned in RTTView)

	static const char *rtName[3]={"GUI_Texture","GUI_Texture","GUI_Texture"};

	// cube side definitions

	static const char *sideName[3]={"side0","side1","side2"};
	static const char *sidePlaneName[3]={"sideplane0","sideplane1","sideplane2"};

	Ogre::Plane sidePlane[3];
	
	sidePlane[0].normal = Ogre::Vector3::NEGATIVE_UNIT_X;
	sidePlane[1].normal = Ogre::Vector3::UNIT_Z;
	sidePlane[2].normal = Ogre::Vector3::UNIT_X;

	for (i=0;i<3;i++) sidePlane[i].d=1.0f;

	Ogre::MaterialPtr sideMaterial[3];
	Ogre::Entity* sideEntity[3];


	// create materials for 3 cube sides

	for(i=0;i<3;i++)
	{
		sideMaterial[i] = Ogre::MaterialManager::getSingleton().create("RttMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		sideMaterial[i]->getTechnique(0)->getPass(0)->setLightingEnabled(false);
		sideMaterial[i]->getTechnique(0)->getPass(0)->createTextureUnitState(rtName[i]);
	}


	// create 3 cube side meshes

	for(i=0;i<3;i++)
	{
		Ogre::MeshManager::getSingleton().createPlane(sidePlaneName[i],
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			sidePlane[i], 
			2.0f, 2.0f,
			1, 1,
			true, 1,
			1.0f, 1.0f,
			Ogre::Vector3::UNIT_Y);

	}

	// create entities , assign materials and attach to scene graph

	for(i=0;i<3;i++)
	{
		sideEntity[i] = mSceneMgr->createEntity(sideName[i],sidePlaneName[i]);
		sideEntity[i]->setMaterial(sideMaterial[i]);

		mSceneMgr->getRootSceneNode()->attachObject(sideEntity[i]);
	}	


	// initial camera setup

	mCamera->setNearClipDistance(1);

	targetSide=0;
	currentRotation=0.0f;

	update();



}

void CubeView::setTargetSide(int n)
{
	targetSide=n;
}

void CubeView::update()
{
	float targetRotation = (float)targetSide * 3.1415927f / 2.0f;

	mCamera->setPosition(Ogre::Vector3(cosf(currentRotation)*4.0f,0.0f,sinf(currentRotation)*4.0f));
	mCamera->lookAt(Ogre::Vector3(0,0,0));

	currentRotation = currentRotation * 0.8 + targetRotation * 0.2;

}