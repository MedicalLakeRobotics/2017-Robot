// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// Accel to cruise speed when cruise distance is exceeded use decel pwr to brake to a stop

#include "TestFwd2Cmd.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

TestFwd2Cmd::TestFwd2Cmd(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void TestFwd2Cmd::Initialize() {
	GetTestData();
	SetTimeout(m_TO);

	line = "Debug, Drivetrain, Starting TestFwd 2 Cmd";
	line += " AccelPwr=" + std::to_string(m_accelPwr);
	line += " CruiseSpeed=" + std::to_string(m_cruiseSpeed);
	line += " CruisePwr=" + std::to_string(m_cruisePwr);
	line += " CruiseDist=" + std::to_string(m_cruiseDist);
	line += " DecelPwr=" + std::to_string(m_decelPwr);
	line += " TO=" + std::to_string(m_TO);
	Robot::logger->appendLog(line);

	Robot::drivetrain->ResetEncoders();
	Robot::drivetrain->SetFirstTimeFlag(0);
	motionStartedFlag = 0;
	m_hitCruiseSpeedFlag = 0;	// we havent hit cruise speed yet
	m_RemainDist = m_cruiseDist;
	Robot::drivetrain->PutZoneData(5, m_cruiseSpeed,  m_cruiseDist, m_RemainDist, m_accelPwr);


	m_currPwr = m_accelPwr;
	Robot::drivetrain->TankDrive(m_currPwr, m_currPwr);
	//std::cout << "TetsFwd2 Init" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void TestFwd2Cmd::Execute() {

	m_drivetrainCurrDist = Robot::drivetrain->GetAverageDist();
	m_drivetrainCurrSpeed = Robot::drivetrain->GetAverageSpeed();
	m_RemainDist = m_cruiseDist - m_drivetrainCurrDist;

	if (m_drivetrainCurrSpeed > 0.5 ) motionStartedFlag = 1;

	if ((m_drivetrainCurrSpeed >= m_cruiseSpeed) && ( m_hitCruiseSpeedFlag == 0)) {
		// once we hit druse speed from accel pwr to cruise pwr till end
		m_hitCruiseSpeedFlag = 1;
		m_currPwr = m_cruisePwr;
	}

	if (m_RemainDist <= 0){
		// we have gone as far ar requested, time to brake to a stop
		m_currPwr = m_decelPwr;
	}

	Robot::drivetrain->PutZoneData(5, m_cruiseSpeed,  m_cruiseDist, m_RemainDist, m_currPwr);
	Robot::drivetrain->TankDrive(m_currPwr, m_currPwr);
}

// Make this return true when this Command no longer needs to run execute()
bool TestFwd2Cmd::IsFinished() {
	if (IsTimedOut()) return true;	// used in all modes
	if ((m_drivetrainCurrSpeed <= 0.5) && (motionStartedFlag != 0)){
		// we have finally stopped or close to stop
		return true;
	}
    return false;
}

// Called once after isFinished returns true
void TestFwd2Cmd::End() {
	Robot::drivetrain->StopMtrs();							// stop the motors
	Robot::logger->appendLog("Ending TestFwd 2 Command");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestFwd2Cmd::Interrupted() {
	End();
}

// ------------------------ Get System Test Default Values --------------------
void TestFwd2Cmd::GetTestData(){
	netTable = NetworkTable::GetTable("Preferences");

	m_accelPwr = netTable->GetNumber("Tst2AccelPwr",0);
	m_cruiseSpeed = netTable->GetNumber("Tst2CruiseSpeed",0);
	m_cruisePwr = netTable->GetNumber("Tst2CruisePwr",0);
	m_cruiseDist = netTable->GetNumber("Tst2CruiseDist",0);
	m_decelPwr = netTable->GetNumber("Tst2DecelPwr",0);
	m_TO = netTable->GetNumber("Tst2TO",0);
}
