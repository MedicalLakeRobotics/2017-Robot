// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef TESTFWDCMD_H
#define TESTFWDCMD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TestFwdCmd: public Command {
public:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
	TestFwdCmd();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();


	typedef struct Test{
		double Vel, Dist, TO, Mode;
	} Test;
	Test fwdTest;

	typedef struct Profile{
		double CruiseSpeed, CruisePwr, StartofZone, EndofZone, AccelPwr, AccelDist, DecelPwr, DecelDist;
	} Profile;
	Profile ZoneArray[5];

	int zoneNum;
	double zonePwr;

	double drivetrainCurrDist, drivetrainCurrVel;


private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES
	std::string line;

	std::shared_ptr<NetworkTable> netTable;			// NetTables to talk to RoboRealm
	std::vector<std::string> keys;

	double m_RemainTgtDist, m_CurrTgtDist;
	char m_Zone;

	void GetTestData();
	void GetProfileData();
	double GetZoneSpeed(int zone);
	double GetZonePwr(int zone);
	double CalcPIDValue(double currVel, double tgtVel);

};

#endif
