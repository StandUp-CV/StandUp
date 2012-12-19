
#ifndef __AnimationBuilder_h_
#define __AnimationBuilder_h_

#include "stdafx.h"
#include "AnimationBuilder.h"

class AnimationBuilder
{
public:
	AnimationBuilder(void);
	~AnimationBuilder(void);
	
	void createAnimations( CEGUI::String v1, CEGUI::String v2, CEGUI::String v3, CEGUI::String r1, CEGUI::String r2, CEGUI::String r3 );
	void yRotation(CEGUI::Animation* anim,CEGUI::String valueStart, CEGUI::String value);
	void unifiedXPositionInterpolation(CEGUI::Animation* anim, CEGUI::String pos1, CEGUI::String pos2);
	CEGUI::Animation* createAnimation(CEGUI::String name, float duration, CEGUI::Animation::ReplayMode replayMode);
	void fadeInAlpha(CEGUI::Animation* anim, CEGUI::String a1, CEGUI::String a2);
};

#endif // #ifndef __AnimationBuilder_h_