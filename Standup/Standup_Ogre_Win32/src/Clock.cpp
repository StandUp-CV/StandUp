
#include "stdafx.h"

#include "Clock.h"

// get the offset from gmt to local time in seconds

const time_t Clock::gmtoff()
{
	// select a value that is high enough
	// so that mktime can produce a valid result
	// ( computed value in secs never < 0 )

	const time_t t=100000;

	// fill a tm structure with the gm time
	tm *li=gmtime(&t);

	// convert back using local time
	int secs=mktime(li);

	// compute difference
	return secs-t;

}
	
// get the seconds passed since 1/1/1970
// (wrapper for c library)
	
const time_t Clock::getCurrentSecond() { static time_t t; time(&t); return t; };

// fill a tm structure
// (wrapper for c library)

const tm& Clock::getDisplayTime(const time_t &second) { static tm *lt; lt=localtime(&second); return *lt; };



AlarmClock::AlarmClock()
{

	alarmState = INACTIVE;

	snoozeTime = 60; // Clock::HOUR;
	prerunTime = 5;  // Clock::HOUR;

	timeOfLastUpdate = 0;
	alarmTime = 0;


}

void AlarmClock::setAlarmTime( time_t t) { if (alarmState!=INACTIVE) throw clex; alarmTime = t; }
void AlarmClock::setActive ( bool state) { alarmState=state?ACTIVE:INACTIVE; }

// Hady Created for display Alarmtime
//static const time_t getAlarmTime() {return alarmTime;};

void AlarmClock::hookAlarmEventHandler ( AlarmEventHandler *handler ) { alarmEventHandler = handler; }

void AlarmClock::watchPerson ( Person *p ) { peopleWatched.push_back( p ); }

bool AlarmClock::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	// helper variable
	bool anyoneSleeping=false;

	// get person count
	std::vector <Person>::size_type i, npeople;
	npeople = peopleWatched.size();

	// now
	time_t ct = Clock::getCurrentSecond();

	switch(alarmState)
	{
	case ACTIVE:
		if (isCurrent(ct,alarmTime-prerunTime))
		{
			// alarm is activated and prerun time is reached
			// tell camera to begin its prerun and change state

			alarmEventHandler->watchOutEvent();
			alarmState = MOVEMENT;
		}
		break;

	case MOVEMENT:
		
		// check wether anyone is sleeping

		for(i=0;i<npeople;++i)
		{
			switch(peopleWatched[i]->getCurrentState())
			{
			case SLEEPING:
			case SLUMBERING:
				anyoneSleeping=true;
			}

		}

		if (ct>alarmTime && anyoneSleeping)
		{
			// if someone is sleeping and time of alarm is reached,
			// ring alarm and change state

			alarmEventHandler->alarmEvent();
			alarmState = AWAKENING;
			//actualTimeOfAlarm = ct;

		}

		if (!anyoneSleeping && isCurrent(ct,alarmTime+snoozeTime))
		{
			// noone is sleeping and the snooze time has run out
			// reset state machine to its original state
			// and set alarm to next day

			alarmState = ACTIVE;
			alarmTime += Clock::DAY;
			alarmEventHandler->everythingCompleteEvent();
		}

		break;

	case AWAKENING:
		for (i=0; i< npeople; ++i)
		{
			time_t pt = peopleWatched[i]->getLastActionTime();

			switch(peopleWatched[i]->getCurrentState())
			{
			case SLEEPING:
			case SLUMBERING:
				anyoneSleeping=true;
				break;

			case GOTUP:
				if (isCurrent(pt,alarmTime+snoozeTime))
				{
					// this person can be regarded as totally awake

					peopleWatched[i]->finallyAwakeEvent();
				}
				break;
			}
		}

		if (anyoneSleeping)
		{
		
		}
		else
		{
			// noone is sleeping anymore

			alarmEventHandler->stopRingingEvent();
			alarmState = MOVEMENT;
		}

		break;

	}


	// keep track of last update time
	timeOfLastUpdate=ct;

	return true;
}
