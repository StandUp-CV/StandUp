
#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>
#include <vector>
#include <string>
#include <exception>

// enums for the state machines

enum AlarmState { ACTIVE, INACTIVE, MOVEMENT, AWAKENING };
enum PersonState { SLEEPING, SLUMBERING, GOTUP, AWAKE };

//-------------------------------------------------------------------------------------

class ClockException : std::exception
{
	std::string what() { return "ClockException"; }
};

//-------------------------------------------------------------------------------------
// Class that get access to the c time lib

class Clock
{
	public:

	// get the offset from gmt to local time in seconds

	static const time_t gmtoff()
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
	
	static const time_t getCurrentSecond() { static time_t t; time(&t); return t; };

	// fill a tm structure
	// (wrapper for c library)

	static const tm& getDisplayTime(const time_t &second) { static tm *lt; lt=localtime(&second); return *lt; };

	// constants for conversion between seconds and hours or days, respectively

	static const time_t HOUR = (60*60);
	static const time_t DAY = (HOUR*24);


};


//-------------------------------------------------------------------------------------
// handles the systems events for the alarm clock

class AlarmEventHandler
{
public:

	// triggered one hour before alarm should ring,
	// the camera should start its prerun at this point
	virtual void watchOutEvent() = 0;

	// triggered at the exact moment when the alarm should ring
	virtual void alarmEvent() = 0;

	// triggered when the should stop ringing
	virtual void stopRingingEvent() = 0;

	// triggered when the wake-up cycle is complete
	// and the alarm state machine has gone back to its default state
	virtual void everythingCompleteEvent() = 0;
};

//-------------------------------------------------------------------------------------
// Represents a person with its values for the alarm clock

class Person
{
private:

	// the state this person is in
	PersonState state;

	// time of this persons last action
	time_t lastActionTime;

	// call this method if something qualified as an action
	void action() { lastActionTime = Clock::getCurrentSecond(); }

public:

	// assume person is sleeping
	// when initializing the state machine
	Person() { state = SLEEPING; lastActionTime=0; }

	const PersonState const getCurrentState() { return state; }
	const time_t const getLastActionTime() { return lastActionTime; }

	// state machine implementation
	void getUpEvent()   { if (state==AWAKE) throw (new ClockException()); state = GOTUP; action(); }
	void getDownEvent() { if (state==AWAKE) throw (new ClockException()); state = SLUMBERING; action(); }
	void finallyAwakeEvent() { if (state!=GOTUP) throw (new ClockException()); state = AWAKE; }


};
//-------------------------------------------------------------------------------------
// Represents a alarm clock in general and the (possible) interface to matlab
class AlarmClock : public Ogre::FrameListener
{
private:

	
	// watch multiple people
	std::vector <Person*> peopleWatched;

	// time, in seconds, frameRenderingQueued() has last been called
	time_t timeOfLastUpdate;


	time_t alarmTime,snoozeTime,prerunTime;
	//time_t actualTimeOfAlarm;

	AlarmState alarmState;
	AlarmEventHandler *alarmEventHandler;

	bool isCurrent(time_t ct, time_t event) { return ct>=event && event>timeOfLastUpdate; }

	ClockException clex;

public:

	AlarmClock()
	{
		alarmState = INACTIVE;
		snoozeTime = Clock::HOUR;
		prerunTime = Clock::HOUR;
	}

	void setAlarmTime( time_t t) { if (alarmState!=INACTIVE) throw clex; alarmTime = t; }
	void setActive ( bool state) { alarmState=state?ACTIVE:INACTIVE; }

	// Hady Created for display Alarmtime
	//static const time_t getAlarmTime() {return alarmTime;};

	void hookAlarmEventHandler ( AlarmEventHandler *handler ) { alarmEventHandler = handler; }

	void watchPerson ( Person *p ) { peopleWatched[0] = p; }

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) override
	{
		bool anyoneSleeping=false;

		std::vector <Person>::size_type i, npeople;
		npeople = peopleWatched.size();

		time_t ct = Clock::getCurrentSecond();

		switch(alarmState)
		{
		case ACTIVE:
			if (isCurrent(ct,alarmTime-prerunTime))
			{
				alarmEventHandler->watchOutEvent();
				alarmState = MOVEMENT;
			}
			break;

		case MOVEMENT:
			
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
				alarmEventHandler->alarmEvent();
				alarmState = AWAKENING;
				//actualTimeOfAlarm = ct;

			}

			if (!anyoneSleeping && isCurrent(ct,alarmTime+snoozeTime))
			{
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
						peopleWatched[i]->finallyAwakeEvent();
					}
					break;
				}
			}

			if (anyoneSleeping)
			{
				//alarmEventHandler->alarmEvent();
				//actualTimeOfAlarm = ct;
			}
			else
			{
				alarmEventHandler->stopRingingEvent();
				alarmState = MOVEMENT;
			}

			break;

		}



		timeOfLastUpdate=ct;
		return true;
	}
};


#endif
