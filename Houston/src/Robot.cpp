// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "WPILib.h"

#include "Commands/AutoCtrGearCmdGrp.h"
#include "Commands/AutoCtrLineCmdGrp.h"

#include "Commands/AutoBoilerLeftGearCmdGrp.h"
#include "Commands/AutoBoilerLeftLineCmdGrp.h"
#include "Commands/AutoBoilerRightGearCmdGrp.h"
#include "Commands/AutoBoilerRightLineCmdGrp.h"

#include "Commands/AutoChutesLeftGearCmdGrp.h"
#include "Commands/AutoChutesLeftLineCmdGrp.h"
#include "Commands/AutoChutesRightGearCmdGrp.h"
#include "Commands/AutoChutesRightLineCmdGrp.h"

#include "Commands/AutoDoNothingCmdGrp.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<FuelHandler> Robot::fuelHandler;
std::shared_ptr<Vision> Robot::vision;
std::shared_ptr<Lighting> Robot::lighting;
std::shared_ptr<Winch> Robot::winch;
std::shared_ptr<Smartdash> Robot::smartdash;
std::shared_ptr<Logger> Robot::logger;
std::shared_ptr<GearHandler> Robot::gearHandler;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION


void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    drivetrain.reset(new Drivetrain());
    fuelHandler.reset(new FuelHandler());
    vision.reset(new Vision());
    lighting.reset(new Lighting());
    winch.reset(new Winch());
    smartdash.reset(new Smartdash());
    logger.reset(new Logger());
    gearHandler.reset(new GearHandler());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	autoCmd.reset(new AutoDoNothingCmdGrp());

	locChooser.AddObject("1 Left", new std::string("Left"));
	locChooser.AddDefault("2 Center", new std::string("Ctr"));
	locChooser.AddObject("3 Right", new std::string("Right"));
	SmartDashboard::PutData("Choose-Location", &locChooser);

	actionChooser.AddDefault("1 Do Nothing", new std::string("Nothing"));
	actionChooser.AddObject("2 Cross Line Only", new std::string("Line"));
	actionChooser.AddObject("3 Place Gear", new std::string("Gear"));
	SmartDashboard::PutData("Choose-Action", &actionChooser);

	tgtChooser.AddDefault("1 Boiler", new std::string("Boiler"));
	tgtChooser.AddObject("2 Chutes", new std::string("Chutes"));
	SmartDashboard::PutData("Choose-Side-Object", &tgtChooser);

  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	// **** add code to print out log at system time > 2'28
	sysTimer.Reset();			// System timer for Competition run
	Robot::drivetrain->ResetGyro();
	sysTimer.Start();
	Robot::logger->appendLog("AutonomousInit started");
	std::cout << "AutonomousInit running" << std::endl;
	DriverStation::Alliance color;
	color = DriverStation::GetInstance().GetAlliance();
	if (color == DriverStation::Alliance::kBlue){
		Robot::logger->appendLog("Alliance Color = BLUE");
	} else {
		Robot::logger->appendLog("Alliance Color = RED");
	}

	std::string locChoice = *(std::string*) locChooser.GetSelected();
	std::string actionChoice = *(std::string*) actionChooser.GetSelected();
	std::string tgtChoice = *(std::string*) tgtChooser.GetSelected();

	if (actionChoice == "Nothing"){
		std::cout << "Do Nothing Selected" << std::endl;
		Robot::logger->appendLog("Do Nothing Selected");
		autoCmd.reset(new AutoDoNothingCmdGrp());
	}
	if ((locChoice == "Ctr") && (actionChoice == "Gear")) {
		std::cout << "Center Gear Selected" << std::endl;
		Robot::logger->appendLog("Center Gear Selected");
		autoCmd.reset(new AutoCtrGearCmdGrp());
	}
	else if ((locChoice == "Ctr") && (actionChoice == "Line")) {
		std::cout << "Center Line Selected" << std::endl;
		Robot::logger->appendLog("Center Line Selected");
		autoCmd.reset(new AutoCtrLineCmdGrp());
	}

	else if ((locChoice == "Left") && (actionChoice == "Gear") && (tgtChoice == "Boiler")) {
		std::cout << "Left Boiler Gear Selected" << std::endl;
		Robot::logger->appendLog("Left Boiler Gear Selected");
		autoCmd.reset(new AutoBoilerLeftGearCmdGrp());
	}
	else if ((locChoice == "Left") && (actionChoice == "Gear") && (tgtChoice == "Chutes")) {
		std::cout << "Left Chutes Gear Selected" << std::endl;
		Robot::logger->appendLog("Left Chutes Gear Selected");
		autoCmd.reset(new AutoChutesLeftGearCmdGrp());
	}

	else if ((locChoice == "Right") && (actionChoice == "Gear") && (tgtChoice == "Boiler")) {
		std::cout << "Right Boiler Gear Selected" << std::endl;
		Robot::logger->appendLog("Right Boiler Gear Selected");
		autoCmd.reset(new AutoBoilerRightGearCmdGrp());
	}
	else if ((locChoice == "Right") && (actionChoice == "Gear") && (tgtChoice == "Chutes")) {
		std::cout << "Right Chutes Gear Selected" << std::endl;
		Robot::logger->appendLog("Right Chutes Gear Selected");
		autoCmd.reset(new AutoChutesRightGearCmdGrp());
	}

	else if ((locChoice == "Left") && (actionChoice == "Line") && (tgtChoice == "Boiler")) {
		std::cout << "Left Boiler Line Selected" << std::endl;
		Robot::logger->appendLog("Left Boiler Line Selected");
		autoCmd.reset(new AutoBoilerLeftLineCmdGrp());
	}
	else if ((locChoice == "Left") && (actionChoice == "Line") && (tgtChoice == "Chutes")) {
		std::cout << "Left Chutes Line Selected" << std::endl;
		Robot::logger->appendLog("Left Chutes Line Selected");
		autoCmd.reset(new AutoChutesLeftLineCmdGrp());
	}

	else if ((locChoice == "Right") && (actionChoice == "Line") && (tgtChoice == "Boiler")) {
		std::cout << "Right Boiler Line Selected" << std::endl;
		Robot::logger->appendLog("Right Boiler Line Selected");
		autoCmd.reset(new AutoBoilerRightLineCmdGrp());
	}
	else if ((locChoice == "Right") && (actionChoice == "Line") && (tgtChoice == "Chutes")) {
		std::cout << "Right Chutes Line Selected" << std::endl;
		Robot::logger->appendLog("Right Chutes Line Selected");
		autoCmd.reset(new AutoChutesRightLineCmdGrp());
	}


	if (autoCmd.get() != nullptr)
		autoCmd->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.

	std::cout << "TeleopInit" << std::endl;

	Robot::logger->appendLog("Stopping Autonomous");
	Robot::logger->appendLog("Starting Teleop");
	Robot::logger->printLog();
	if (autoCmd.get() != nullptr)
		autoCmd->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	// **** ad code here to look at system clock and print log if time > 2'25 sec ???
}

void Robot::TestPeriodic() {
	lw->Run();
}

// ******************************************************************************
// *****                     User Initialize Method                          ****
// ******************************************************************************
void Robot::UserInit(){
	std::cout << "UserInit Started" << std::endl;
//	netTable = NetworkTable::GetTable("Preferences");		// point to preferences table

	// ---------------- Initialize Gyro & Encoders ----------------------------
	Robot::drivetrain->ResetGyro();
	Robot::drivetrain->ResetEncoders();
}


START_ROBOT_CLASS(Robot);

