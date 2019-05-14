// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<SpeedController> drivetrainFrontLeftSpdCtr;
	static std::shared_ptr<SpeedController> drivetrainFrontRightSpdCtr;
	static std::shared_ptr<SpeedController> drivetrainRearLeftSpdCtr;
	static std::shared_ptr<SpeedController> drivetrainRearRightSpdCtr;
	static std::shared_ptr<RobotDrive> drivetrainRobotDrive41;
	static std::shared_ptr<Encoder> drivetrainLeftDriveEncoder;
	static std::shared_ptr<Encoder> drivetrainRightDriveEncoder;
	static std::shared_ptr<AnalogInput> drivetrainIrProxLeft;
	static std::shared_ptr<AnalogInput> drivetrainIrProxRight;
	static std::shared_ptr<AnalogInput> drivetrainSonar;
	static std::shared_ptr<DigitalInput> drivetrainProbeLmtSw;
	static std::shared_ptr<SpeedController> fuelHandlerFuelCollSpdCtrl;
	static std::shared_ptr<SpeedController> fuelHandlerFuelDisSpdCtrl;
	static std::shared_ptr<SpeedController> fuelHandlerFuelShakerSpdCtrl;
	static std::shared_ptr<Encoder> fuelHandlerFuelDisEnc;
	static std::shared_ptr<DigitalInput> winchWinchLmtSw;
	static std::shared_ptr<SpeedController> winchWinchSpdCtr;
	static std::shared_ptr<Relay> gearHandlerGearEjectSpike;
	static std::shared_ptr<Relay> gearHandlerGearRotSpike;
	static std::shared_ptr<DigitalInput> gearHandlerGearEjectFwdLmtSw;
	static std::shared_ptr<DigitalInput> gearHandlerGearEjectRearLmtSw;
	static std::shared_ptr<AnalogPotentiometer> gearHandlerGearTransPot;
	static std::shared_ptr<DigitalInput> gearHandlerGearTransLeftLmtSw;
	static std::shared_ptr<DigitalInput> gearHandlerGearRotateSnsr;
	static std::shared_ptr<DigitalInput> gearHandlerGearTransRightLmtSw;
	static std::shared_ptr<DigitalInput> gearHandlerGearLoadedSnsr;
	static std::shared_ptr<SpeedController> gearHandlerGearTransSpdCtrl;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	static void init();
};
#endif
