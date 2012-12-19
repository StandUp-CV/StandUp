
#ifndef CAMERATEST
#define CAMERATEST

#include "Sound.h"
#include "Clock.h"

enum InputTest { GETUP, LAYDOWN, ISAWAKE };

class CameraTest : public AlarmEventHandler
{
private:

	Sound* mSound;
	AlarmClock* mAlarmClock;
	Person* mPerson;

public:

	CameraTest ()
	{
		mSound = NULL;
		mAlarmClock = NULL;
		mPerson = NULL;

		mSound = new Sound();

		mAlarmClock = new AlarmClock();
		mPerson = new Person();

		mAlarmClock->watchPerson(mPerson);
		mAlarmClock->hookAlarmEventHandler(this);
	}

	~CameraTest ()
	{
		if (mSound) delete mSound;
		if (mAlarmClock) delete mAlarmClock;
		if (mPerson) delete mPerson;
	}

	AlarmClock* getAlarmClock()
	{
		return this->mAlarmClock;
	}
	
	void watchOutEvent()
	{
	}

	void alarmEvent()
	{
	}

	void stopRingingEvent()
	{
	}

	void everythingCompleteEvent()
	{
	}

	void inputTest(InputTest what)
	{
		switch(what)
		{
		case GETUP:

			mPerson->getUpEvent();
			break;

		case LAYDOWN:

			mPerson->getDownEvent();
			break;

		case ISAWAKE:

			mPerson->finallyAwakeEvent();
			break;
		}
	}


};

#endif
