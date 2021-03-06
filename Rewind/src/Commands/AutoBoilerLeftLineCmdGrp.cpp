// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "AutoBoilerLeftLineCmdGrp.h"
#include "AutoDriveFwdCmd.h"
#include "DrivePointTurnCmd.h"
#include "DelayCmd.h"
#include "VisionUpdate.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoBoilerLeftLineCmdGrp::AutoBoilerLeftLineCmdGrp() {
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
     // Add Commands here:
    // e.g. AddSequential(new Command1());
    //      AddSequential(new Command2());
    // these will run in order.

    // To run multiple commands at the same time,
    // use AddParallel()
    // e.g. AddParallel(new Command1());
    //      AddSequential(new Command2());
    // Command1 and Command2 will run in parallel.

    // A command group will require all of the subsystems that each member
    // would require.
    // e.g. if Command1 requires chassis, and Command2 requires arm,
    // a CommandGroup containing them would require both the chassis and the
    // arm.
              // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
                      // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS

	// 							   (tgtDist, accelPwr, cruisePwr, decelPwr, slowPwr, stopPwr, accelDist, decelDist, slowSpeed, stopDist, TO, Mode)
	AddSequential(new AutoDriveFwdCmd(90.25,     0.25,      0.25,      -0.0,     0.05,    -0.20,      3,       3,         0.0,       0.2,   5,   0));

	// (Angle, Speed, Timeout, Mode (0=by angle, 1=Left Side CW, 2=Right Side CCW)
	AddSequential(new DrivePointTurnCmd(10, 0.4, 8, 1));

	// -------- Delay 2/10'second for vision to get image ------------
	AddSequential(new DelayCmd(0.2));

	// -------- Update Vision Data ------------
	AddSequential(new VisionUpdate());
}
