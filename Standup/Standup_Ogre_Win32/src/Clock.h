/// \file src\Clock.h
///
/// \brief Declares the clock class.

#ifndef CLOCK_H

/// \def CLOCK_H
///
/// \brief A macro that defines clock h.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define CLOCK_H

/// \enum AlarmState
///
/// \brief enums for the state machines.

enum AlarmState { ACTIVE, INACTIVE, MOVEMENT, AWAKENING };

/// \enum PersonState
///
/// \brief Values that represent PersonState.

enum PersonState { SLEEPING, SLUMBERING, GOTUP, AWAKE };

// -------------------------------------------------------------------------------------. 

/// \class ClockException
///
/// \brief Exception for signalling clock errors.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class ClockException : std::exception
{
	/// \fn std::string ClockException::what()
	///
	/// \brief Gets the what.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return .

	std::string what() { return "ClockException"; }
};

/// \class Clock
///
/// \brief Class that get access to the c time lib.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class Clock
{
	public:

	/// \fn static const time_t Clock::gmtoff();
	///
	/// \brief get the offset from gmt to local time in seconds.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return .

	static const time_t gmtoff();

	/// \fn static const time_t Clock::getCurrentSecond();
	///
	/// \brief get the seconds passed since 1/1/1970 (wrapper for c library)
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return The current second.
	
	static const time_t getCurrentSecond();

	/// \fn static const tm& Clock::getDisplayTime(const time_t &second);
	///
	/// \brief fill a tm structure (wrapper for c library)
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param second
	/// The second.
	///
	/// \return The display time.
	
	static const tm& getDisplayTime(const time_t &second);

	// constants for conversion between seconds and hours or days, respectively

	static const time_t HOUR = (60*60); /*!< The hour */
	static const time_t DAY = (HOUR*24);	/*!< The day */


};

/// \class AlarmEventHandler
///
/// \brief handles the systems events for the alarm clock.
///
/// \author Hans Ferchland
/// \date 19.12.2012

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

	/// \fn virtual void AlarmEventHandler::everythingCompleteEvent() = 0;
	///
	/// \brief triggered when the wake-up cycle is complete and the alarm state machine has gone
	/// back to its default state.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	virtual void everythingCompleteEvent() = 0;
};

/// \class Person
///
/// \brief Represents a person with its values for the alarm clock.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class Person
{
private:

	PersonState state; /*!< the state this person is in */
	time_t lastActionTime;  /*!< Time of the last action */

	/// \fn void Person::action()
	///
	/// \brief call this method if something qualified as an action.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void action() { lastActionTime = Clock::getCurrentSecond(); }

public:

	/// \fn Person::Person()
	///
	/// \brief assume person is sleeping when initializing the state machine.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	Person() { state = SLEEPING; lastActionTime=0; }

	/// \fn const PersonState const Person::getCurrentState()
	///
	/// \brief Gets current state.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return The current state.

	const PersonState const getCurrentState() { return state; }

	/// \fn const time_t const Person::getLastActionTime()
	///
	/// \brief Gets the last action time.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return The last action time.

	const time_t const getLastActionTime() { return lastActionTime; }

	// State machine implementation

	/// \fn void Person::getUpEvent()
	///
	/// \brief state machine implementation.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \exception ClockException
	/// Thrown when a Clock error condition occurs.

	void getUpEvent()   { if (state==AWAKE) throw (new ClockException()); state = GOTUP; action(); }

	/// \fn void Person::getDownEvent()
	///
	/// \brief Gets down event.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \exception ClockException
	/// Thrown when a Clock error condition occurs.

	void getDownEvent() { if (state==AWAKE) throw (new ClockException()); state = SLUMBERING; action(); }

	/// \fn void Person::finallyAwakeEvent()
	///
	/// \brief Finally awake event.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \exception ClockException
	/// Thrown when a Clock error condition occurs.

	void finallyAwakeEvent() { if (state!=GOTUP) throw (new ClockException()); state = AWAKE; }


};

/// \class AlarmClock
///
/// \brief Represents a alarm clock in general and the (possible) interface to matlab.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class AlarmClock : public Ogre::FrameListener
{
private:

	/// \property std::vector <Person*> peopleWatched
	///
	/// \brief watch multiple people.
	///
	/// \return The people watched.

	std::vector <Person*> peopleWatched;

	// time, in seconds, frameRenderingQueued() has last been called
	time_t timeOfLastUpdate;	/*!< Time of the last update */

	/// \property time_t alarmTime,snoozeTime,prerunTime
	///
	/// \brief Gets the time of the prerun.
	///
	/// \return The time of the prerun.

	time_t alarmTime,snoozeTime,prerunTime;

	AlarmState alarmState;  /*!< State of the alarm */
	AlarmEventHandler *alarmEventHandler;   /*!< The alarm event handler */

	/// \fn bool AlarmClock::isCurrent(time_t ct, time_t event)
	///
	/// \brief Query if 'ct' is current.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param ct
	/// The ct.
	/// \param event
	/// The event.
	///
	/// \return true if current, false if not.

	bool isCurrent(time_t ct, time_t event) { return ct>=event && event>timeOfLastUpdate; }

	ClockException clex;	/*!< Details of the exception */

public:

	/// \fn AlarmClock::AlarmClock();
	///
	/// \brief Default constructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	AlarmClock();

	/// \fn void AlarmClock::setAlarmTime( time_t t);
	///
	/// \brief Sets alarm time.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param t
	/// The time_t to process.

	void setAlarmTime( time_t t);

	/// \fn void AlarmClock::setActive ( bool state);
	///
	/// \brief Sets an active.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param state
	/// true to state.

	void setActive ( bool state);

	/// \fn void AlarmClock::hookAlarmEventHandler ( AlarmEventHandler *handler );
	///
	/// \brief Handler, called when the hook alarm event.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] handler
	/// If non-null, the handler.

	void hookAlarmEventHandler ( AlarmEventHandler *handler );

	/// \fn void AlarmClock::watchPerson ( Person *p );
	///
	/// \brief Watch person.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param [in,out] p
	/// If non-null, the Person * to process.

	void watchPerson ( Person *p );

	/// \fn bool AlarmClock::frameRenderingQueued(const Ogre::FrameEvent& evt) override;
	///
	/// \brief Frame rendering queued.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param evt
	/// The event.
	///
	/// \return true if it succeeds, false if it fails.

	bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;
};


#endif
