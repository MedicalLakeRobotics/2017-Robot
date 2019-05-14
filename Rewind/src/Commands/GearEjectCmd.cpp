// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "GearEjectCmd.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GearEjectCmd::GearEjectCmd(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::gearHandler.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GearEjectCmd::Initialize() {
	line = "Debug, Gear, Starting GearEjectCmd Init";
	Robot::logger->appendLog(line);
	//std::cout << "Starting GearEjectCmd Init" << std::endl;
	SetTimeout(5);
	ejectFlag = 0;
}

// Called repeatedly when this Command is scheduled to run
void GearEjectCmd::Execute() {
	// request to eject gear
	if (Robot::gearHandler->GetEjectFwdLmtSw() != true) {
		//we haven't hit the end so keep moving forward
		Robot::gearHandler->EjectMotorFwd();}
	else {
		// we have hit the end we need to stop
		Robot::gearHandler->EjectMotorStop();
		ejectFlag = 1;}
}

// Make this return true when this Command no longer needs to run execute()
bool GearEjectCmd::IsFinished() {
	if (IsTimedOut()) 		return true;
	if (ejectFlag == 1 ) 	return true;	// we are back so exit
    return false;
}

// Called once after isFinished returns true
void GearEjectCmd::End() {
	Robot::gearHandler->EjectMotorStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearEjectCmd::Interrupted() {
	End();
}