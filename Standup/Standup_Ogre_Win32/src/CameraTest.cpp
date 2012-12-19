
#include "stdafx.h"

#include "CameraTest.h"
#include "StandupApplication.h"

CameraTest::CameraTest ()
{
	mSound = NULL;
	mAlarmClock = NULL;
	mPerson = NULL;

	mSound = new Sound();

	mAlarmClock = new AlarmClock();
	mPerson = new Person();

	mAlarmClock->watchPerson(mPerson);
	mAlarmClock->hookAlarmEventHandler(this);

	StandupApplication::getInstance()->getRoot()->addFrameListener(mAlarmClock);
}

CameraTest::~CameraTest ()
{
	if (mSound) delete mSound;
	if (mAlarmClock) delete mAlarmClock;
	if (mPerson) delete mPerson;
}

AlarmClock* CameraTest::getAlarmClock()
{
	return this->mAlarmClock;
}
	
void CameraTest::watchOutEvent()
{
	int i=0;
	i++;
}

void CameraTest::alarmEvent()
{
}

void CameraTest::stopRingingEvent()
{
}

void CameraTest::everythingCompleteEvent()
{
}

void CameraTest::inputTest(InputTest what)
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

