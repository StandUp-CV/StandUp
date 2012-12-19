
#ifndef CAMERATEST
#define CAMERATEST

enum InputTest { GETUP, LAYDOWN, ISAWAKE };

class CameraTest : public AlarmEventHandler
{
private:

	Sound* mSound;
	AlarmClock* mAlarmClock;
	Person* mPerson;

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

};

#endif
