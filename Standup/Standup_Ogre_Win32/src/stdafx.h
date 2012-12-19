

#include <time.h>

#include <sstream>
#include <string>

#include <vector>
#include <exception>

// Ogre headers you need

#include <Ogre.h>
#include <OgreMaterialManager.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgrePrerequisites.h>
#include <OgreStringConverter.h>

// OIS include

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

// CEGUI include

#include <CEGUI.h>
#include <CEGUIOgreRenderer.h>
#include <CEGUIOgreRenderTarget.h>
#include <CEGUIOgreImageCodec.h>
#include <CEGUISystem.h>
#include <CEGUISlider.h>


// FMOD

#include <fmod.hpp>
#include <fmod_errors.h>


#include "Sound.h"
#include "Clock.h"


// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif