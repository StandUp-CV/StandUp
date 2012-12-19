/// \file src\GUI.h
///
/// \brief Declares the graphical user interface class.

#ifndef __GUI_h_

/// \def __GUI_h_();
///
/// \brief A macro that defines graphical user interface h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define __GUI_h_

using namespace CEGUI;

/// \class GUI
///
/// \brief Class that handles the gui creation and animation.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class GUI : public Ogre::FrameListener 
{
public:

	/// \fn GUI::GUI(CEGUI::System* system, Ogre::Root* root);
	///
	/// \brief Constructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] system
	/// If non-null, the system.
	/// \param [in,out] root
	/// If non-null, the root.

	GUI(CEGUI::System* system, Ogre::Root* root);

	/// \fn GUI::~GUI(void);
	///
	/// \brief Destructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	~GUI(void);

	/// \fn void GUI::createScene(void);
	///
	/// \brief Creates the scene.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void createScene(void);

	/// \fn void GUI::createDialog1( WindowManager &wmgr );
	///
	/// \brief Creates dialog 1.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] wmgr
	/// The wmgr.

	void createDialog1( WindowManager &wmgr );

	/// \fn void GUI::createDialog2( WindowManager &wmgr );
	///
	/// \brief Creates dialog 2.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] wmgr
	/// The wmgr.

	void createDialog2( WindowManager &wmgr );

	/// \fn void GUI::createDialog3( WindowManager &wmgr );
	///
	/// \brief Creates dialog 3.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] wmgr
	/// The wmgr.

	void createDialog3( WindowManager &wmgr );

	/// \fn Ogre::TexturePtr GUI::createCEGUI_RTTScene();
	///
	/// \brief Creates cegui rtt scene.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return The new cegui rtt scene.

	Ogre::TexturePtr createCEGUI_RTTScene();

	/// \fn void GUI::setAnimationInstances();
	///
	/// \brief Sets animation instances.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void setAnimationInstances();

	/************************************************************************/
	/* Events                                                               */
	/************************************************************************/

	/// \fn bool GUI::dialog1ButtonLeftClicked(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 1 button left clicked.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog1ButtonLeftClicked(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog1ButtonRightClicked(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 1 button right clicked.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog1ButtonRightClicked(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog2ButtonRightClicked(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 2 button right clicked.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog2ButtonRightClicked(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog3ButtonLeftClicked(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 3 button left clicked.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog3ButtonLeftClicked(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::checkBoxClicked(const CEGUI::EventArgs& );
	///
	/// \brief Check box clicked.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool checkBoxClicked(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog1ButtonLeftHoverIn(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 1 button left hover in.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog1ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog1ButtonRightHoverIn(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 1 button right hover in.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog1ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog2ButtonRightHoverIn(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 2 button right hover in.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog2ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog3ButtonLeftHoverIn(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 3 button left hover in.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog3ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog1ButtonLeftHoverOut(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 1 button left hover out.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog1ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog1ButtonRightHoverOut(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 1 button right hover out.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog1ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog2ButtonRightHoverOut(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 2 button right hover out.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog2ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::dialog3ButtonLeftHoverOut(const CEGUI::EventArgs& );
	///
	/// \brief Dialog 3 button left hover out.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param parameter1
	/// The first parameter.
	///
	/// \return true if it succeeds, false if it fails.

	bool dialog3ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/);

	/// \fn bool GUI::frameRenderingQueued(const Ogre::FrameEvent& evt);
	///
	/// \brief Frame rendering queued.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param evt
	/// The event.
	///
	/// \return true if it succeeds, false if it fails.

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/// \fn void GUI::update(const Ogre::FrameEvent& evt);
	///
	/// \brief Updates the given evt.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param evt
	/// The event.

	void update(const Ogre::FrameEvent& evt);

	/// \fn int GUI::getSliderValueMin(float f);
	///
	/// \brief Finds the slidervaluemin of the given arguments.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param f
	/// The float to process.
	///
	/// \return The calculated slider value minimum.

	int GUI::getSliderValueMin(float f);

	/// \fn int GUI::getSliderValueHour(float f);
	///
	/// \brief Gets slider value hour.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param f
	/// The float to process.
	///
	/// \return The slider value hour.

	int GUI::getSliderValueHour(float f);

	/// \fn String GUI::getSliderTimeString(float f);
	///
	/// \brief Gets slider time string.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param f
	/// The float to process.
	///
	/// \return The slider time string.

	String getSliderTimeString(float f);

	/// \fn String GUI::getCurrentTimeString(void);
	///
	/// \brief Gets current time string.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return The current time string.

	String getCurrentTimeString(void);

private:

	/// \fn void GUI::initialiseRTTViewport(CEGUI::RenderingSurface* const surface);
	///
	/// \brief Initialises the rtt viewport.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] surface
	/// If non-null, the surface.

	void initialiseRTTViewport(CEGUI::RenderingSurface* const surface);

	/// \fn float GUI::getCurrentTimePosition();
	///
	/// \brief Gets current time position.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return The current time position.

	float getCurrentTimePosition();
	CEGUI::System* mSystem; /*!< The system */
	FrameWindow* mDialogWindow1;	/*!< The first m dialog window */
	FrameWindow* mDialogWindow2;	/*!< The second m dialog window */
	FrameWindow* mDialogWindow3;	/*!< The third m dialog window */
	FrameWindow* mainWindow;	/*!< The main window */
	DefaultWindow* mDialog2AlarmTime;   /*!< Time of the dialog 2 alarm */
	DefaultWindow* mDialog2CurrentTime; /*!< Time of the dialog 2 current */
	DefaultWindow* mDialog2StateInfo;   /*!< Information describing the dialog 2 state */
	DefaultWindow* mDialog1TextClock;   /*!< The dialog 1 text clock */
	DefaultWindow* mDialog1TextAlarm;   /*!< The dialog 1 text alarm */
	DefaultWindow* mDialog2CurrentTimeHelper;   /*!< The dialog 2 current time helper */
	DefaultWindow* mDialog2Clock;   /*!< The dialog 2 clock */
	PushButton* mDialog1ButtonRight;	/*!< The dialog 1 button right */
	PushButton* mDialog1ButtonLeft; /*!< The dialog 1 button left */
	PushButton* mDialog3ButtonLeft; /*!< The dialog 3 button left */
	PushButton* mDialog2ButtonRight ;   /*!< The dialog 2 button right */
	Checkbox* mDialog2Checkbox; /*!< The dialog 2 checkbox */
	Slider* mDialog2Slider; /*!< The dialog 2 slider */
	Window* mWindowRoot;	/*!< The window root */
	bool mMoveLeft; /*!< true to move left */
	bool mMoveRight;	/*!< true to move right */
	bool mIsAlarmActive;	/*!< true if this GUI is alarm active */
	// saves the current time and gmt offset
	int mCurrentSeconds;	/*!< The current seconds */
	int mCurrentMinutes;	/*!< The current minutes */
	int mCurrentHours;  /*!< The current hours */
	int mHourFormat;	/*!< The hour format */
	int mAlarmMinutes;  /*!< The alarm in minutes */
	int mAlarmHours;	/*!< The alarm in hours */

	Ogre::Camera* mCamera;  /*!< The camera */
	Ogre::SceneManager* mRTTSceneMgr;   /*!< Manager for rtt scene */
	Ogre::RenderTarget *mRenderTarget;  /*!< The render target */
	Ogre::Viewport* mViewport;  /*!< The viewport */

	AnimationBuilder* mAnimationBuilder;	/*!< The animation builder */
	// AnimationInstance
	AnimationInstance* instAnim_MoveWindow1Right;   /*!< The instance animation move window 1 right */
	AnimationInstance* instAnim_MoveWindow2Right;   /*!< The instance animation move window 2 right */
	AnimationInstance* instAnim_MoveWindow1Left;	/*!< The instance animation move window 1 left */
	AnimationInstance* instAnim_MoveWindow3Left;	/*!< The instance animation move window 3 left */
	AnimationInstance* instAnim_moveWindow1FromRightToStart;	/*!< The instance animation move window 1 from right to start */
	AnimationInstance* instAnim_moveWindow2FromLeftToStart; /*!< The instance animation move window 2 from left to start */
	AnimationInstance* instAnim_moveWindow1FromLeftToStart; /*!< The instance animation move window 1 from left to start */
	AnimationInstance* instAnim_moveWindow3FromRightToStart;	/*!< The instance animation move window 3 from right to start */
	AnimationInstance* instAnim_FadeIn1;	/*!< The first instance animation fade in */
	AnimationInstance* instAnim_FadeOut;	/*!< The instance animation fade out */

	//RTT Utils
	Ogre::Viewport *mRTTViewport;   /*!< The rtt viewport */
	Ogre::Camera *mRTTCam;  /*!< The rtt camera */
	Ogre::RenderTexture *mOgreRenderTexture;	/*!< The ogre render texture */

	CameraTest *mCameraTest;	/*!< The camera test */

};

#endif // #ifndef __GUI_h_
