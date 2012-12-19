
#ifndef __GUI_h_
#define __GUI_h_

using namespace CEGUI;

// Class that handles the gui creation and animation
class GUI : public Ogre::FrameListener 
{
public:



	GUI(CEGUI::System* system, Ogre::Root* root);

	~GUI(void);

	void createScene(void);

	void createDialog1( WindowManager &wmgr );

	void createDialog2( WindowManager &wmgr );

	void createDialog3( WindowManager &wmgr );

	Ogre::TexturePtr createCEGUI_RTTScene();

	void setAnimationInstances() ;

	/************************************************************************/
	/* Events                                                               */
	/************************************************************************/
	

	bool dialog1ButtonLeftClicked(const CEGUI::EventArgs& /*e*/);

	bool dialog1ButtonRightClicked(const CEGUI::EventArgs& /*e*/);

	bool dialog2ButtonRightClicked(const CEGUI::EventArgs& /*e*/);

	bool dialog3ButtonLeftClicked(const CEGUI::EventArgs& /*e*/);

	bool checkBoxClicked(const CEGUI::EventArgs& /*e*/);

	bool dialog1ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/);

	bool dialog1ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/);

	bool dialog2ButtonRightHoverIn(const CEGUI::EventArgs& /*e*/);

	bool dialog3ButtonLeftHoverIn(const CEGUI::EventArgs& /*e*/);

	bool dialog1ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/);

	bool dialog1ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/);

	bool dialog2ButtonRightHoverOut(const CEGUI::EventArgs& /*e*/);

	bool dialog3ButtonLeftHoverOut(const CEGUI::EventArgs& /*e*/);

	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	void update(const Ogre::FrameEvent& evt);

	int GUI::getSliderValueMin(float f);

	int GUI::getSliderValueHour(float f);

	String getSliderTimeString(float f);

	String getCurrentTimeString(void);

private:
	void initialiseRTTViewport(CEGUI::RenderingSurface* const surface);
	float getCurrentTimePosition();
	CEGUI::System* mSystem;

	FrameWindow* mDialogWindow1;
	FrameWindow* mDialogWindow2;
	FrameWindow* mDialogWindow3;
	FrameWindow* mainWindow;
	DefaultWindow* mDialog2AlarmTime;
	DefaultWindow* mDialog2CurrentTime;
	DefaultWindow* mDialog2StateInfo;
	DefaultWindow* mDialog1TextClock;
	DefaultWindow* mDialog1TextAlarm;
	DefaultWindow* mDialog2CurrentTimeHelper;
	DefaultWindow* mDialog2Clock;
	PushButton* mDialog1ButtonRight;
	PushButton* mDialog1ButtonLeft;
	PushButton* mDialog3ButtonLeft;
	PushButton* mDialog2ButtonRight ;
	Checkbox* mDialog2Checkbox;
	Slider* mDialog2Slider;
	Window* mWindowRoot;
	bool mMoveLeft;
	bool mMoveRight;
	bool mIsAlarmActive;
	// saves the current time and gmt offset
	int mCurrentSeconds;
	int mCurrentMinutes;
	int mCurrentHours;
	int mHourFormat;
	int mAlarmMinutes;
	int mAlarmHours;

	Ogre::Camera* mCamera;
	Ogre::SceneManager* mRTTSceneMgr;
	Ogre::RenderTarget *mRenderTarget;
	Ogre::Viewport* mViewport;

	AnimationBuilder* mAnimationBuilder;
	// AnimationInstance
	AnimationInstance* instAnim_MoveWindow1Right;
	AnimationInstance* instAnim_MoveWindow2Right;
	AnimationInstance* instAnim_MoveWindow1Left;
	AnimationInstance* instAnim_MoveWindow3Left;
	AnimationInstance* instAnim_moveWindow1FromRightToStart;
	AnimationInstance* instAnim_moveWindow2FromLeftToStart;
	AnimationInstance* instAnim_moveWindow1FromLeftToStart;
	AnimationInstance* instAnim_moveWindow3FromRightToStart;
	AnimationInstance* instAnim_FadeIn1;
	AnimationInstance* instAnim_FadeOut;


	//RTT Utils
	Ogre::Viewport *mRTTViewport;
	Ogre::Camera *mRTTCam;
	Ogre::RenderTexture *mOgreRenderTexture;	


	CameraTest *mCameraTest;

};

#endif // #ifndef __GUI_h_
