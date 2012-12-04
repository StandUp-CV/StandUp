
#ifndef __RTTView_h_
#define __RTTView_h_

#include "stdafx.h"
#include "BaseView.h"

#define CUBEFACE_SIZE 1024

class RTTView : public BaseView
{
public:
	RTTView (Ogre::Root *root, Ogre::String &instanceName) : BaseView(root,instanceName){}
	 Ogre::RenderTarget& getRenderTarget() override;

protected:
	virtual void setupRenderTarget(void);
	Ogre::TexturePtr rtt_texture ;
};

#endif
