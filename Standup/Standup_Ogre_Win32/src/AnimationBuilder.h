/// \file src\AnimationBuilder.h
///
/// \brief Declares the animation builder class.

#ifndef __AnimationBuilder_h_

/// \def __AnimationBuilder_h_
///
/// \brief A macro that defines animation builder h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define __AnimationBuilder_h_

#include "stdafx.h"
#include "AnimationBuilder.h"

/// \class AnimationBuilder
///
/// \brief Animation builder.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class AnimationBuilder
{
public:

	/// \fn AnimationBuilder::AnimationBuilder(void);
	///
	/// \brief Default constructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	AnimationBuilder(void);

	/// \fn AnimationBuilder::~AnimationBuilder(void);
	///
	/// \brief Destructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	~AnimationBuilder(void);

	/// \fn void AnimationBuilder::createAnimations( CEGUI::String v1, CEGUI::String v2,
	/// CEGUI::String v3, CEGUI::String r1, CEGUI::String r2, CEGUI::String r3 );
	///
	/// \brief Creates the animations.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param v1
	/// The first CEGUI::String.
	/// \param v2
	/// The second CEGUI::String.
	/// \param v3
	/// The third CEGUI::String.
	/// \param r1
	/// The first CEGUI::String.
	/// \param r2
	/// The second CEGUI::String.
	/// \param r3
	/// The third CEGUI::String.

	void createAnimations( CEGUI::String v1, CEGUI::String v2, CEGUI::String v3, CEGUI::String r1, CEGUI::String r2, CEGUI::String r3 );

	/// \fn void AnimationBuilder::yRotation(CEGUI::Animation* anim,CEGUI::String valueStart,
	/// CEGUI::String value);
	///
	/// \brief Y coordinate rotations.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] anim
	/// If non-null, the animation.
	/// \param valueStart
	/// The value start.
	/// \param value
	/// The value.

	void yRotation(CEGUI::Animation* anim,CEGUI::String valueStart, CEGUI::String value);

	/// \fn void AnimationBuilder::unifiedXPositionInterpolation(CEGUI::Animation* anim,
	/// CEGUI::String pos1, CEGUI::String pos2);
	///
	/// \brief Unified x coordinate position interpolation.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] anim
	/// If non-null, the animation.
	/// \param pos1
	/// The first position.
	/// \param pos2
	/// The second position.

	void unifiedXPositionInterpolation(CEGUI::Animation* anim, CEGUI::String pos1, CEGUI::String pos2);

	/// \fn CEGUI::Animation* AnimationBuilder::createAnimation(CEGUI::String name, float duration,
	/// CEGUI::Animation::ReplayMode replayMode);
	///
	/// \brief Creates an animation.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param name
	/// The name.
	/// \param duration
	/// The duration.
	/// \param replayMode
	/// The replay mode.
	///
	/// \return The new animation.

	CEGUI::Animation* createAnimation(CEGUI::String name, float duration, CEGUI::Animation::ReplayMode replayMode);

	/// \fn void AnimationBuilder::fadeInAlpha(CEGUI::Animation* anim, CEGUI::String a1,
	/// CEGUI::String a2);
	///
	/// \brief Fade in alpha.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] anim
	/// If non-null, the animation.
	/// \param a1
	/// The first CEGUI::String.
	/// \param a2
	/// The second CEGUI::String.

	void fadeInAlpha(CEGUI::Animation* anim, CEGUI::String a1, CEGUI::String a2);
};

#endif // #ifndef __AnimationBuilder_h_