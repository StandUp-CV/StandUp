
#include "stdafx.h"

#include "CameraTest.h"
#include "StandupApplication.h"

CameraTest::CameraTest ()
{
	mLabel = NULL;
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
	mLabel->setText("watchOutEvent() was triggered.");
}

void CameraTest::alarmEvent()
{
	mLabel->setText("alarmEvent() was triggered.");
}

void CameraTest::stopRingingEvent()
{
	mLabel->setText("stopRingingEvent() was triggered.");
}

void CameraTest::everythingCompleteEvent()
{
	mLabel->setText("everythingCompleteEvent() was triggered.");
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

