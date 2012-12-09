
#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>
#include <vector>
#include <string>
#include <exception>

enum AlarmState { ACTIVE, INACTIVE, MOVEMENT, AWAKENING };
enum PersonState { SLEEPING, SLUMBERING, GOTUP, AWAKE };

class ClockException : std::exception
{
	std::string what() { return "ClockException"; }
};

class Clock
{
	public:
	
	static const time_t getCurrentSecond() { static time_t t; time(&t); return t; };
	static const tm& getDisplayTime(const time_t &second) { static tm *lt; lt=localtime(&second); return *lt; };

	static const time_t HOUR = (60*60);
	static const time_t DAY = (HOUR*24);


};

class AlarmEventHandler
{
public:

	virtual void watchOutEvent() = 0;
	virtual void alarmEvent() = 0;
	virtual void stopRingingEvent() = 0;
	virtual void everythingCompleteEvent() = 0;


};

class Person
{
private:
	PersonState state;
	time_t lastActionTime;

	void action() { lastActionTime = Clock::getCurrentSecond(); }

public:

	Person() { state = SLEEPING; lastActionTime=0; }

	const PersonState const getCurrentState() { return state; }
	const time_t const getLastActionTime() { return lastActionTime; }

	void getUpEvent()   { if (state==AWAKE) throw (new ClockException()); state = GOTUP; action(); }
	void getDownEvent() { if (state==AWAKE) throw (new ClockException()); state = SLUMBERING; action(); }
	void finallyAwakeEvent() { if (state!=GOTUP) throw (new ClockException()); state = AWAKE; }


};

class AlarmClock
{
private:

	std::vector <Person> allTheLonelyPeople;

	time_t timeOfLastUpdate;

	time_t alarmTime,snoozeTime,prerunTime;
	//time_t actualTimeOfAlarm;

	AlarmState alarmState;
	AlarmEventHandler *alarmEventHandler;

	bool isCurrent(time_t ct, time_t event) { return ct>=event && event>timeOfLastUpdate; }

public:

	AlarmClock()
	{
		snoozeTime = Clock::HOUR;
		prerunTime = Clock::HOUR;
	}

	void setAlarmTime( time_t t) { if (alarmState!=INACTIVE) throw ( new ClockException ); alarmTime = t; }

	void hookAlarmEventHandler ( AlarmEventHandler *handler ) { alarmEventHandler = handler; }

	void update()
	{
		bool anyoneSleeping=false;

		std::vector <Person>::size_type i, npeople;
		npeople = allTheLonelyPeople.size();

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
				switch(allTheLonelyPeople[i].getCurrentState())
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
				time_t pt = allTheLonelyPeople[i].getLastActionTime();

				switch(allTheLonelyPeople[i].getCurrentState())
				{
				case SLEEPING:
				case SLUMBERING:
					anyoneSleeping=true;
					break;

				case GOTUP:
					if (isCurrent(pt,alarmTime+snoozeTime))
					{
						allTheLonelyPeople[i].finallyAwakeEvent();
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
	}
};


#endif
