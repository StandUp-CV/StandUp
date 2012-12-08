#include "stdafx.h"
#include "RTTView.h"

void RTTView::setupRenderTarget(void)
{
	rtt_texture = Ogre::TextureManager::getSingleton().createManual(mInstanceName + "_texture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, CUBEFACE_SIZE, CUBEFACE_SIZE, 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);

	Ogre::RenderTexture *renderTexture = rtt_texture->getBuffer()->getRenderTarget();

	//renderTexture->getViewport(0)->setClearEveryFrame(true);
	//renderTexture->getViewport(0)->setOverlaysEnabled(false);

	mRenderTarget = renderTexture;
}

