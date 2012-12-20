
/// \file src\CameraTest.h
///
/// \brief Declares the CameraTest class.

#ifndef CAMERATEST
#define CAMERATEST

/// \enum InputTest
///
/// \brief events that could hypotetically be triggered by the computer vision code

enum InputTest { GETUP, LAYDOWN, ISAWAKE };

/// \class CameraTest
///
/// \brief Camera test. test class for webcam. input of computer vision part is simulated.
///
/// \author Roman Hillebrand
/// \date 19.12.2012

class CameraTest : public AlarmEventHandler
{
private:

	Sound* mSound;  /*!< The sound object */
	AlarmClock* mAlarmClock;	/*!< The alarm clock object */
	Person* mPerson;	/*!< The person object */

	CEGUI::DefaultWindow *mLabel;   /*!< The label object */

public:

	/// \fn void CameraTest::watchOutEvent();
	///
	/// \brief inherited from AlarmEventHandler. 
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	void watchOutEvent();

	/// \fn void CameraTest::alarmEvent();
	///
	/// \brief inherited from AlarmEventHandler.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	void alarmEvent();

	/// \fn void CameraTest::stopRingingEvent();
	///
	/// \brief inherited from AlarmEventHandler.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	void stopRingingEvent();

	/// \fn void CameraTest::everythingCompleteEvent();
	///
	/// \brief inherited from AlarmEventHandler.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	void everythingCompleteEvent();

	/// \fn CameraTest::CameraTest ();
	///
	/// \brief creates Sound, AlarmClock and Person objects and registers event handlers.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	CameraTest ();

	/// \fn CameraTest::~CameraTest ();
	///
	/// \brief destroys Sound, AlarmClock and Person objects.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012

	~CameraTest ();

	/// \fn AlarmClock* CameraTest::getAlarmClock();
	///
	/// \brief get a reference to the AlarmClock member.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \return null if it fails, else the alarm clock.

	AlarmClock* getAlarmClock();

	/// \fn void CameraTest::inputTest(InputTest what);
	///
	/// \brief called by GUI to simulate computer vision triggered events.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param what
	/// what event to simulate.

	void inputTest(InputTest what);

	/// \fn void CameraTest::setOutputLabel(CEGUI::DefaultWindow* label)
	///
	/// \brief called by GUI to specify a label which should display the corresponding texts, should an event occur.
	///
	/// \author Roman Hillebrand
	/// \date 19.12.2012
	///
	/// \param [in,out] label
	/// If non-null, the label.

	void setOutputLabel(CEGUI::DefaultWindow* label) { mLabel=label; }

};

#endif
