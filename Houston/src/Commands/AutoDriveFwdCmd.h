// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef AUTODRIVEFWDCMD_H
#define AUTODRIVEFWDCMD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutoDriveFwdCmd: public Command {
public:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
	AutoDriveFwdCmd(double tgtDist, double accelPwr, double cruisePwr, double decelPwr, double slowPwr, double stopPwr, double accelDist, double decelDist, double slowSpeed, double stopDist, int TO, int Mode);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES

    double m_tgtDist;
    double m_accelPwr;
    double m_cruisePwr;
    double m_decelPwr;
    double m_slowPwr;
    double m_stopPwr;
    double m_accelDist;
    double m_decelDist;
    double m_slowSpeed;
    double m_stopDist;
    int m_TO;
    int m_Mode;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES

    std::string line;

	std::shared_ptr<NetworkTable> netTable;			// NetTables to talk to RoboRealm
	std::vector<std::string> keys;

	//Timer stallTmr, stopTmr;
	int driveModeFlag, driveProfileFlag, stopFlag;

	double currPwr;
	double tgtHdg;
	double m_RemainTgtDist, m_CurrTgtDist, currDist, currSpeed;
	char m_Zone;
	bool motionFlag;

	void SendPwrToDrivetrain(double speed, int mode);
	void ProcessBrake();
};

#endif