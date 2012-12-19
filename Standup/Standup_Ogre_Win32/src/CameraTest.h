
#ifndef CAMERATEST
#define CAMERATEST

enum InputTest { GETUP, LAYDOWN, ISAWAKE };


// test class for webcam
// input of computer vision part is simulated

class CameraTest : public AlarmEventHandler
{
private:

	Sound* mSound;
	AlarmClock* mAlarmClock;
	Person* mPerson;

	CEGUI::DefaultWindow *mLabel;

public:

	// inherited from AlarmEventHandler

	void watchOutEvent();
	void alarmEvent();
	void stopRingingEvent();
	void everythingCompleteEvent();

	// computer vision simulation

	CameraTest ();
	~CameraTest ();
	AlarmClock* getAlarmClock();
	void inputTest(InputTest what);

	void setOutputLabel(CEGUI::DefaultWindow* label) { mLabel=label; }

};

#endif
