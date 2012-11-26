
#ifndef __CubeView_h_
#define __CubeView_h_

#include "stdafx.h"
#include "BaseView.h"

class CubeView : public BaseView
{
public:
	CubeView (Ogre::Root *root, Ogre::String &instanceName) : BaseView(root,instanceName){}
	virtual void update();
	void setTargetSide(int n);

protected:
	virtual void createScene();
	virtual void setupRenderTarget(void);


	Ogre::TexturePtr mTexture;

	float currentRotation;
	int targetSide;

};

#endif
