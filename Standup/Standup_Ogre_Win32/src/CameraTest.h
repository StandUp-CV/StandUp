/// \file src\CameraTest.h
///
/// \brief Declares the camera test class.

#ifndef CAMERATEST

/// \def CAMERATEST
///
/// \brief A macro that defines cameratest.
///
/// \author Hans Ferchland
/// \date 19.12.2012

#define CAMERATEST

/// \enum InputTest
///
/// \brief Values that represent InputTest.

enum InputTest { GETUP, LAYDOWN, ISAWAKE };

/// \class CameraTest
///
/// \brief Camera test.
///
/// \author Hans Ferchland
/// \date 19.12.2012

class CameraTest : public AlarmEventHandler
{
private:

	Sound* mSound;  /*!< The sound */
	AlarmClock* mAlarmClock;	/*!< The alarm clock */
	Person* mPerson;	/*!< The person */

public:

	/// \fn void CameraTest::watchOutEvent();
	///
	/// \brief inherited from AlarmEventHandler.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void watchOutEvent();

	/// \fn void CameraTest::alarmEvent();
	///
	/// \brief Alarm event.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void alarmEvent();

	/// \fn void CameraTest::stopRingingEvent();
	///
	/// \brief Stops ringing event.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void stopRingingEvent();

	/// \fn void CameraTest::everythingCompleteEvent();
	///
	/// \brief Everything complete event.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	void everythingCompleteEvent();

	/// \fn CameraTest::CameraTest ();
	///
	/// \brief computer vision simulation.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	CameraTest ();

	/// \fn CameraTest::~CameraTest ();
	///
	/// \brief Destructor.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012

	~CameraTest ();

	/// \fn AlarmClock* CameraTest::getAlarmClock();
	///
	/// \brief Gets alarm clock.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \return null if it fails, else the alarm clock.

	AlarmClock* getAlarmClock();

	/// \fn void CameraTest::inputTest(InputTest what);
	///
	/// \brief Tests input.
	///
	/// \author Hans Ferchland
	/// \date 19.12.2012
	///
	/// \param what
	/// The what.

	void inputTest(InputTest what);

};

#endif
