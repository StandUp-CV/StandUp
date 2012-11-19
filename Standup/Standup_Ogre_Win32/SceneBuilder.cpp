

	/*
	SceneBuilder


*/
#include "stdafx.h"
#include "SceneBuilder.h"


SceneBuilder::SceneBuilder(void)
{
}


SceneBuilder::~SceneBuilder(void)
{
}


//-------------------------------------------------------------------------------------
void SceneBuilder::createScene(void)
{
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create an Entity
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::Entity* ogreHead2 = mSceneMgr->createEntity( "Head2", "ogrehead.mesh" );

	// Create a SceneNode and attach the Entity to it
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	headNode->attachObject(ogreHead);
	Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "HeadNode2", Ogre::Vector3( 100, 0, 0 ) );
	headNode2->attachObject( ogreHead2 );

	// Create a Light and set its position
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);
}