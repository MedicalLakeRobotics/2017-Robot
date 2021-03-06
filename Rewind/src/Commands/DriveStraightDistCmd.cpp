// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveStraightDistCmd.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveStraightDistCmd::DriveStraightDistCmd(double Speed, double Distance, double Timeout, double Mode): Command() {
    m_Speed = Speed;
    m_Distance = Distance;
    m_Timeout = Timeout;
    m_Mode = Mode;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveStraightDistCmd::Initialize() {
	line = "Debug, Drivetrain, Starting DriveStraightDistCmd";
	line += " Speed=" + std::to_string(m_Speed) + " Dist=" + std::to_string(m_Distance);
	line += " TimeOut=" + std::to_string(m_Timeout) + " Mode=" + std::to_string(m_Mode);
	Robot::logger->appendLog(line);
	std::cout << "DriveStraightDistCmd Init" << std::endl;

	GetTestData();
	std::cout << "cruise pwr =" << cruisePwr;
	std::cout << "  tgtDist =" << tgtDist;
	std::cout << "  TO =" << TO << std::endl;
	SetTimeout(TO);
	stallTmr.Reset();
	stallTmr.Start();		// this used to check if we our stalled at the beginning and can safely shutdown
	Robot::drivetrain->ResetEncoders();
	Robot::drivetrain->SetFirstTimeFlag(0);				// set flag to zero for gyro correction
	if (tgtDist < 0) tgtDist = tgtDist * -1;			// Distance is always positive, speed can be negative
	m_RemainTgtDist = tgtDist;
	driveModeFlag = 0;									// We are just starting our will need to accel.
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightDistCmd::Execute() {
	currDist = Robot::drivetrain->GetAverageDist();
	currSpeed = Robot::drivetrain->GetAverageSpeed();
	m_RemainTgtDist = tgtDist - currDist;
	if (currSpeed > 0)	stallTmr.Reset();		// reset so we can measure how long we have been stopped

	if (driveModeFlag == 0){
		// were starting to accelerate
		driveModeFlag = 1;
		if (cruisePwr < accelPwr) {
			currPwr = cruisePwr; }
		else {
			currPwr = accelPwr; }
	}

	if (driveModeFlag == 1){
		// were are accelerating up to the first accel distance end pt.
		if (currDist > accelDist){
			driveModeFlag = 2;						// we need to move on to cruise speed now
			currPwr =  cruisePwr; }
	}

	if (driveModeFlag == 2){
		// we are now continuing at cruise speed till we need to decelerate
		if (m_RemainTgtDist <= decelDistFromTgt){
			driveModeFlag = 3;						// we need to decelerate now
			currPwr =  decelPwr; }
	}

	if (driveModeFlag == 3){
		// we're decelerating to a slow more precise speed
		if (currSpeed <= 10){
			driveModeFlag = 4;	// we are now at our slow speed continue at 0.3 pwr
			currPwr =  slowPwr; }
	}


	if (driveModeFlag == 4){
		// we have reached our slow speed now need to look for point to break to a stop
		if (m_RemainTgtDist <= stopDistFromTgt){
			driveModeFlag = 5;				// we now need to decel to a stop
			currPwr =  stopPwr; }
	}

	if (m_RemainTgtDist <= 0){
		// if we have gone to far lets break to a stop regardless of driveModeFlag
		currPwr =  -0.05;
		std::cout << "  We may have over run target DISTANCE" << std::endl;
	}

	Robot::drivetrain->PutZoneData( 8, 0, tgtDist, m_RemainTgtDist, currPwr);
	SendPwrToDrivetrain( currPwr, 1);
	std::cout << "  Drive mode flag = " << driveModeFlag;
	std::cout << "  currDist ="  << currDist;
	std::cout << "  RemainTgtDist ="  << m_RemainTgtDist;
	std::cout << "  CurrSpeed ="  << currSpeed ;
	return;
}


// Make this return true when this Command no longer needs to run execute()
bool DriveStraightDistCmd::IsFinished() {
	if (IsTimedOut()) return true;	// used in all modes

	if ( (currSpeed <= 0) && (stallTmr.Get() > 0.05 )){
		// Make sure we are past the slow start, end when stopped
		std::cout << "We have stopped" << std::endl;
		return true;		// we have stopped so end
	}

	 return false;
}

// Called once after isFinished returns true
void DriveStraightDistCmd::End() {
	Robot::drivetrain->StopMtrs();							// stop the motors
	Robot::logger->appendLog("Ending DriveStraightDistCmd");
	std::cout << "DriveStraightDistCmd End" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightDistCmd::Interrupted() {
	End();
}

// -------------------------------------------------------------
//                     User Defined Methods
// -------------------------------------------------------------

void DriveStraightDistCmd::SendPwrToDrivetrain(double speed, int mode){
	if (mode==0) Robot::drivetrain->TankDrive(speed, speed);

	if (mode==1) Robot::drivetrain->Drive(speed, 0);
}


// ------------------------ Get System Test Default Values --------------------
void DriveStraightDistCmd::GetTestData(){
	netTable = NetworkTable::GetTable("Preferences");

	cruisePwr = netTable->GetNumber("Vel",0);
	tgtDist = netTable->GetNumber("Dist",0);
	TO = netTable->GetNumber("TO",0);
	mode = netTable->GetNumber("Mode",0);

	accelPwr = netTable->GetNumber("DaccelPwr",0.5);
	accelDist = netTable->GetNumber("DaccelDist",2);
	decelDistFromTgt = netTable->GetNumber("DdecelDist",10);
	stopDistFromTgt = netTable->GetNumber("DstopDist",1);
	decelPwr = netTable->GetNumber("DdecelPwr",-0.25);
	slowPwr = netTable->GetNumber("DslowPwr",-0.25);
	stopPwr = netTable->GetNumber("DstopPwr",-0.25);
}

