
/// \file src\Clock.h
///
/// \brief Declares the Clock, AlarmEventHandler, Person and AlarmClock classes.

#ifndef CLOCK_H
#define CLOCK_H

/// \enum AlarmState
///
/// \brief enums for the AlarmClock state machine.

enum AlarmState { ACTIVE, INACTIVE, MOVEMENT, AWAKENING };

/// \enum PersonState
///
/// \brief enums for the Person state machine.

enum PersonState { SLEEPING, SLUMBERING, GOTUP, AWAKE };

/// \class ClockException
///
/// \brief Exception for signalling clock errors. Inherited from std::exception.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class ClockException : std::exception
{
	/// \fn std::string ClockException::what()
	///
	/// \brief name of the exception.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \return "ClockException"

	std::string what() { return "ClockException"; }
};

/// \class Clock
///
/// \brief wrapper class for the c library header time.h. static class.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class Clock
{
	public:

	/// \fn static const time_t Clock::gmtoff();
	///
	/// \brief get the offset from gmt to local time in seconds.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \return time in seconds

	static const time_t gmtoff();

	/// \fn static const time_t Clock::getCurrentSecond();
	///
	/// \brief get the seconds passed since 1/1/1970 (wrapper for c library)
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \return time in seconds
	
	static const time_t getCurrentSecond();

	/// \fn static const tm& Clock::getDisplayTime(const time_t &second);
	///
	/// \brief fill a tm structure (wrapper for c library)
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param second
	/// seconds since 1/1/1970
	///
	/// \return input converted to a tm struct

	static const tm& getDisplayTime(const time_t &second);

	// constants for conversion between seconds and hours or days, respectively

	static const time_t HOUR = (60*60); /*!< seconds per hour */
	static const time_t DAY = (HOUR*24);	/*!< seconds per day */


};

/// \class AlarmEventHandler
///
/// \brief abstract class, inherited by CameraTest. Handles events triggered by AlarmClock.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class AlarmEventHandler
{
public:

	/// \fn virtual void AlarmEventHandler::watchOutEvent() = 0;
	///
	/// \brief triggered one hour before alarm should ring, the camera should start its prerun at this point.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	virtual void watchOutEvent() = 0;

	/// \fn virtual void AlarmEventHandler::alarmEvent() = 0;
	///
	/// \brief triggered at the exact moment when the alarm should ring.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	virtual void alarmEvent() = 0;

	/// \fn virtual void AlarmEventHandler::stopRingingEvent() = 0;
	///
	/// \brief triggered when the should stop ringing.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	virtual void stopRingingEvent() = 0;

	/// \fn virtual void AlarmEventHandler::everythingCompleteEvent() = 0;
	///
	/// \brief triggered when the wake-up cycle is complete and the alarm state machine has gone back to its default state.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	virtual void everythingCompleteEvent() = 0;
};

/// \class Person
///
/// \brief Represents one persons state for use with the alarm clock.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class Person
{
private:

	PersonState state; /*!< the state this person is in */

	time_t lastActionTime;  /*!< Time of this persons last action */

	/// \fn void Person::action()
	///
	/// \brief call this method if something qualified as an action.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	void action() { lastActionTime = Clock::getCurrentSecond(); }

public:

	/// \fn Person::Person()
	///
	/// \brief assume person is sleeping when initializing the state machine.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	Person() { state = SLEEPING; lastActionTime=0; }

	/// \fn const PersonState const Person::getCurrentState()
	///
	/// \brief Gets current state.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \return The current state.

	const PersonState const getCurrentState() { return state; }

	/// \fn const time_t const Person::getLastActionTime()
	///
	/// \brief Gets the time of this persons last action.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \return time in seconds.

	const time_t const getLastActionTime() { return lastActionTime; }

	// state machine implementation

	/// \fn void Person::getUpEvent()
	///
	/// \brief called by computer vision part when a corresponding movement has been detected.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \exception ClockException
	/// Thrown when a Clock error condition occurs.

	void getUpEvent()   { if (state==AWAKE) throw (new ClockException()); state = GOTUP; action(); }

	/// \fn void Person::getDownEvent()
	///
	/// \brief called by computer vision part when a corresponding movement has been detected.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \exception ClockException
	/// Thrown when a Clock error condition occurs.

	void getDownEvent() { if (state==AWAKE) throw (new ClockException()); state = SLUMBERING; action(); }

	/// \fn void Person::finallyAwakeEvent()
	///
	/// \brief called by computer vision part when a corresponding movement has been detected.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \exception ClockException
	/// Thrown when a Clock error condition occurs.

	void finallyAwakeEvent() { if (state!=GOTUP) throw (new ClockException()); state = AWAKE; }

};

/// \class AlarmClock
///
/// \brief Represents an alarm clock in general and the (possible) interface to matlab.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class AlarmClock : public Ogre::FrameListener
{
private:

	/// \property std::vector <Person*> peopleWatched
	///
	/// \brief all the people that should get up.

	std::vector <Person*> peopleWatched;

	time_t timeOfLastUpdate;	/*!< time, in seconds, frameRenderingQueued() has last been called */

	time_t alarmTime,snoozeTime,prerunTime;

	AlarmState alarmState;  /*!< current state of the state machine */
	AlarmEventHandler *alarmEventHandler;   /*!< which object to notify of changes */

	/// \fn bool AlarmClock::isCurrent(time_t ct, time_t event)
	///
	/// \brief did this happen in between the last event and now?
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param ct
	/// The current time in seconds.
	/// \param event
	/// The time when te event triggered in seconds.
	///
	/// \return true if current, false if not.

	bool isCurrent(time_t ct, time_t event) { return ct>=event && event>timeOfLastUpdate; }

	ClockException clex;	/*!< Details of the exception */

public:

	/// \fn AlarmClock::AlarmClock();
	///
	/// \brief Default constructor.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	AlarmClock();

	/// \fn void AlarmClock::setAlarmTime( time_t t);
	///
	/// \brief Sets alarm time.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param t
	/// new time of alarm in seconds.

	void setAlarmTime( time_t t);

	/// \fn void AlarmClock::setActive ( bool state);
	///
	/// \brief activate or deactivate the alarm clock (called by GUI).
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param state
	/// true: activate, false: deactivate

	void setActive ( bool state);

	/// \fn void AlarmClock::hookAlarmEventHandler ( AlarmEventHandler *handler );
	///
	/// \brief supply a handler for change events (called by AlarmTest).
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param handler
	/// pointer to the object which should become the alarm event handler.

	void hookAlarmEventHandler ( AlarmEventHandler *handler );

	/// \fn void AlarmClock::watchPerson ( Person *p );
	///
	/// \brief add a person to the list of persons to watch. (called by AlarmTest)
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param p
	/// pointer to the Person object which should be added to the list.

	void watchPerson ( Person *p );

	/// \fn bool AlarmClock::frameRenderingQueued(const Ogre::FrameEvent& evt) override;
	///
	/// \brief update handler.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param evt
	/// The event.
	///
	/// \return true if OGRE should continue rendering.

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;
};


#endif
