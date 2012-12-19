#include "stdafx.h"
#include "AnimationBuilder.h"

AnimationBuilder::AnimationBuilder(void)
{
}


AnimationBuilder::~AnimationBuilder(void)
{
}



//Param startposition of the 3 Windows
void AnimationBuilder::createAnimations( CEGUI::String v1,  CEGUI::String v2,  CEGUI::String v3, CEGUI::String r1, CEGUI::String r2, CEGUI::String r3 )
{
	/************************************************************************/
	/* moveWindow1Right														*/
	/************************************************************************/
	CEGUI::Animation* anim = createAnimation("MoveWindow1Right", 0.6f, CEGUI::Animation::RM_Once);
	unifiedXPositionInterpolation(anim,v1,v3);
	// yRotation
	yRotation(anim,r1,r3);

	/************************************************************************/
	/* moveWindow2Right														*/
	/************************************************************************/
	CEGUI::Animation* anim2 = createAnimation("MoveWindow2Right", 0.6f, CEGUI::Animation::RM_Once);
	unifiedXPositionInterpolation(anim2,v2,v1);
	// yRotation
	yRotation(anim2,r2,r1);


	/************************************************************************/
	/* moveWindow3left														*/
	/************************************************************************/
	CEGUI::Animation* anim3 = createAnimation("MoveWindow3Left", 0.6f, CEGUI::Animation::RM_Once);
	// now we define affector inside our Testing animation
	unifiedXPositionInterpolation(anim3,v3,v1);
	// yRotation
	yRotation(anim3,r3,r1);


	/************************************************************************/
	/* moveWindow1left														*/
	/************************************************************************/
	CEGUI::Animation* anim4 = createAnimation("MoveWindow1Left", 0.6f, CEGUI::Animation::RM_Once);
	unifiedXPositionInterpolation(anim4,v1,v2);
	// yRotation
	yRotation(anim4,r1,r2);


	/************************************************************************/
	/* moveWindow1FromRightToStart														*/
	/************************************************************************/
	CEGUI::Animation* anim5 = createAnimation("moveWindow1FromRightToStart", 0.6f, CEGUI::Animation::RM_Once);
	// now we define affector inside our Testing animation
	unifiedXPositionInterpolation(anim5,v3,v1);
	yRotation(anim5,r3,r1);


	/************************************************************************/
	/* moveWindow1FromLeftToStart														*/
	/************************************************************************/
	CEGUI::Animation* anim6 = createAnimation("moveWindow1FromLeftToStart", 0.6f, CEGUI::Animation::RM_Once);
	unifiedXPositionInterpolation(anim6,v2,v1);
	yRotation(anim6,r2,r1);


	/************************************************************************/
	/* moveWindow2FromStarttoLeft														*/
	/************************************************************************/
	CEGUI::Animation* anim7 = createAnimation("moveWindow2FromLeftToStart", 0.6f, CEGUI::Animation::RM_Once);
	unifiedXPositionInterpolation(anim7,v1,v2);
	// yRotation
	yRotation(anim7,r1,r2);


	/************************************************************************/
	/* moveWindow3FromStartTORight														*/
	/************************************************************************/
	CEGUI::Animation* anim8 = 	createAnimation("moveWindow3FromRightToStart", 0.6f, CEGUI::Animation::RM_Once);
	// now we define affector inside our Testing animation
	unifiedXPositionInterpolation(anim8,v1,v3);
	// yRotation
	yRotation(anim8,r1, r3);

	
	/************************************************************************/
	/*                          FadeIn1                                            */
	/************************************************************************/
	CEGUI::Animation* anim9 = 	createAnimation("FadeIn1", 0.6f, CEGUI::Animation::RM_Once);
	fadeInAlpha(anim9,"0.0","0.3f");


/************************************************************************/
/*                          FadeOut                                           */
/************************************************************************/
CEGUI::Animation* anim10 = 	createAnimation("FadeOut", 0.6f, CEGUI::Animation::RM_Once);
	fadeInAlpha(anim10,"0.3f","0");
}


/*
 *	
 *	createAnimation
 *	
 */
CEGUI::Animation* AnimationBuilder::createAnimation(CEGUI::String name, float duration, CEGUI::Animation::ReplayMode replayMode)
{
	CEGUI::Animation* anim = CEGUI::AnimationManager::getSingleton().createAnimation(name);
	anim->setDuration(duration); // duration in seconds
	anim->setReplayMode(replayMode); // when this animation is started, only play it once, then stop
	return anim;
}


/*
 *	
 *	fadeInAlpha
 *	
 */
void AnimationBuilder::fadeInAlpha(CEGUI::Animation* anim, CEGUI::String a1, CEGUI::String a2)
{
	// this affector will again use float interpolator
	CEGUI::Affector* affector = anim->createAffector("Alpha", "float");
	affector->createKeyFrame(0.0f, a1); // at 0.0 seconds, set alpha to 1.0
	affector->createKeyFrame(0.6f, a2, CEGUI::KeyFrame::P_QuadraticDecelerating); // at 0.3 seconds, set alpha to 0.5, now decelerating!
}




/*
 *	
 *	unifiedXPositionInterpolation
 *	
 */
void AnimationBuilder::unifiedXPositionInterpolation(CEGUI::Animation* anim, CEGUI::String pos1, CEGUI::String pos2)
{
	// this affector changes YRotation and interpolates keyframes with float interpolator
	CEGUI::Affector* affector = anim->createAffector("UnifiedXPosition", "UDim");
	// at 0.0 seconds, the animation should set YRotation to 0 degrees
	affector->createKeyFrame(0.0f, pos1);
	// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
	affector->createKeyFrame(0.6f, pos2, CEGUI::KeyFrame::P_QuadraticAccelerating);
}


/*
 *	
 *	yRotation
 *	
 */
void AnimationBuilder::yRotation(CEGUI::Animation* anim, CEGUI::String valueStart , CEGUI::String valueEnd)
	{
		
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim->createAffector("YRotation", "float");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, valueStart);
		// at 0.8 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.6f, valueEnd, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}
