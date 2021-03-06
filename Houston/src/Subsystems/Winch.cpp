// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Winch.h"
#include "../RobotMap.h"
#include "../Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Winch::Winch() : Subsystem("Winch") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    winchLmtSw = RobotMap::winchWinchLmtSw;
    winchSpdCtr = RobotMap::winchWinchSpdCtr;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Winch::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

// --------------- Motor Control -----------------
void Winch::WinchMotorOn(std::shared_ptr<frc::Joystick> joy){
	if (( winchLmtSw->Get() != LIMITSWITCHPRESSED || (joy->GetRawButton(7) == true)))
		winchSpdCtr->Set(1);
//		winchSpike->Set(winchSpike->kForward);
//		winchSpike->Set(winchSpike->kReverse); // if needs reversing
}

void Winch::WinchMotorOff(){
	winchSpdCtr->StopMotor();
//	winchSpike->Set(winchSpike->kOff);
}

// ---------------- Limit Switch Methods ---------------
bool Winch::GetWinchLmtSw(){
	if (winchLmtSw->Get() == LIMITSWITCHPRESSED) return true;
	return false;
}

void Winch::DisplaySmartdashSimple(){

	// ----------- Display Limit Switches -------
	if (winchLmtSw->Get() == LIMITSWITCHPRESSED)
		SmartDashboard::PutString("Winch LmtSw", "Pressed");
	else
		SmartDashboard::PutString("Winch LmtSw", "NOT Pressed");
}
