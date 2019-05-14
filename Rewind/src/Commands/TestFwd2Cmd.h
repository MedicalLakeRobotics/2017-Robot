// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef TESTFWD2CMD_H
#define TESTFWD2CMD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TestFwd2Cmd: public Command {
public:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
	TestFwd2Cmd();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

	// Accel to cruise speed when cruise distance is exceeded use decel pwr to brake to a stop
	double m_accelPwr, m_cruiseSpeed, m_cruisePwr, m_cruiseDist, m_decelPwr, m_TO;
	double m_drivetrainCurrDist, m_RemainDist,  m_drivetrainCurrSpeed;
	double m_currPwr;

	int m_hitCruiseSpeedFlag, motionStartedFlag;

	void GetTestData();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES

	std::string line;
	std::shared_ptr<NetworkTable> netTable;			// NetTables to talk to RoboRealm
	std::vector<std::string> keys;


};

#endif