#include "stdafx.h"
#include "RTTView.h"

#include "CEGUIOgreTexture.h"

void RTTView::setupRenderTarget(void)
{

	mRenderTarget = StandupApplication::getInstance()->getGUIRenderTarget();
}

