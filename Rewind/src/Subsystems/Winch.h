// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef WINCH_H
#define WINCH_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Winch: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<DigitalInput> winchLmtSw;
	std::shared_ptr<SpeedController> winchSpdCtr;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// -------------------- Network Table Pointer -------------------
	std::shared_ptr<NetworkTable> netTable;
	std::vector<std::string> keys;

public:
	Winch();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	// ---------- Public Variables --------------------------------
	const bool LIMITSWITCHPRESSED = true;
	// ---------- Public Methods --------------------------------

	// --------------- Motor Control -----------------
	void WinchMotorOn(std::shared_ptr<frc::Joystick> joy);							// manually drive gear left or right
	void WinchMotorOff();

	// ---------------- Limit Switch Methods ---------------
	bool GetWinchLmtSw();

	void DisplaySmartdashSimple();

};

#endif
