#include "stdafx.h"
#include "AnimationBuilder.h"
#include "OgreStringConverter.h"

AnimationBuilder::AnimationBuilder(void)
{
}


AnimationBuilder::~AnimationBuilder(void)
{
}

//Param startposition of the 3 Windows
void AnimationBuilder::createAnimations( CEGUI::String v1,  CEGUI::String v2,  CEGUI::String v3 )
{
	/************************************************************************/
	/* moveWindow1Right														*/
	/************************************************************************/
	CEGUI::Animation* anim = CEGUI::AnimationManager::getSingleton().createAnimation("MoveWindow1Right");
	anim->setDuration(0.5f); // duration in seconds
	anim->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v1);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v3, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow2Right														*/
	/************************************************************************/
	CEGUI::Animation* anim2 = CEGUI::AnimationManager::getSingleton().createAnimation("MoveWindow2Right");
	anim2->setDuration(0.5f); // duration in seconds
	anim2->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim2->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v2);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v1, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow3left														*/
	/************************************************************************/
	CEGUI::Animation* anim3 = CEGUI::AnimationManager::getSingleton().createAnimation("MoveWindow3Left");
	anim3->setDuration(0.5f); // duration in seconds
	anim3->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim3->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v3);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v1, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow1left														*/
	/************************************************************************/
	CEGUI::Animation* anim4 = CEGUI::AnimationManager::getSingleton().createAnimation("MoveWindow1Left");
	anim4->setDuration(0.5f); // duration in seconds
	anim4->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim4->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v1);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v2, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow1FromRightToStart														*/
	/************************************************************************/
	CEGUI::Animation* anim5 = CEGUI::AnimationManager::getSingleton().createAnimation("moveWindow1FromRightToStart");
	anim5->setDuration(0.5f); // duration in seconds
	anim5->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim5->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v3);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v1, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow1FromLeftToStart														*/
	/************************************************************************/
	CEGUI::Animation* anim6 = CEGUI::AnimationManager::getSingleton().createAnimation("moveWindow1FromLeftToStart");
	anim6->setDuration(0.5f); // duration in seconds
	anim6->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim6->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v2);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v1, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow2FromLeftToStart														*/
	/************************************************************************/
	CEGUI::Animation* anim7 = CEGUI::AnimationManager::getSingleton().createAnimation("moveWindow2FromLeftToStart");
	anim7->setDuration(0.5f); // duration in seconds
	anim7->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim7->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v1);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v2, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

	/************************************************************************/
	/* moveWindow3FromRightToStart														*/
	/************************************************************************/
	CEGUI::Animation* anim8 = CEGUI::AnimationManager::getSingleton().createAnimation("moveWindow3FromRightToStart");
	anim8->setDuration(0.5f); // duration in seconds
	anim8->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop


	// now we define affector inside our Testing animation
	{
		// this affector changes YRotation and interpolates keyframes with float interpolator
		CEGUI::Affector* affector = anim8->createAffector("UnifiedXPosition", "UDim");
		// at 0.0 seconds, the animation should set YRotation to 0 degrees
		affector->createKeyFrame(0.0f, v1);
		// at 0.3 seconds, YRotation should be 10.0 degrees and animation should progress towards this in an accelerating manner
		affector->createKeyFrame(0.5f, v3, CEGUI::KeyFrame::P_QuadraticAccelerating);
	}

}
