// stdafx.h is the header file where you include all those headers 
// you need in your project that rarely or never change. 
// These could be Ogre headers, or anything else you want. 
// The name of this header file doesn't matter, but by 
// convention we name it stdafx.h.

// Ogre headers you need
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
// CEGUI include
#include "CEGUI.h"
#include "CEGUIOgreRenderer.h"
#include "CEGUISystem.h"

// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif