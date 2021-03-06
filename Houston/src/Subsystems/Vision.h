// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef VISION_H
#define VISION_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <thread>
#include <stdio.h>

static std::mutex udpMutex;
static double udpCOGX;
static double udpCOGY;

#define BUFLEN 512  //Max length of buffer
#define PORT 5800   //The port on which to listen for incoming data
#define ROBORIO "10.45.13.2"
	/**
 *
 *
 * @author ExampleAuthor
 */
class Vision: public Subsystem {
private:
	// It's desirablse that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	double COGX,COGY;
	double tipHdg, tipDist;
	double shiftDist, shiftAngle;
	double shiftHdg1, shiftHdg2, shiftFwdDist, shiftAngle1, shiftAngle2, shiftActiveWheelA,shiftActiveWheelB;
	double currYaw, currAngleCorrection;
	double tgtDistance, tgtAngleX, tgtAngleY;
	double adjTgtTransCorrection;		// this is the distance in inches tgt is off ctr at probe tip
	double tgtTransCorrection;			// this is the distance in inches tgt is off ctr at wall
	const double degPerPixel = 0.17798;
	int validTgtFlag;

public:

	static void udpRcvr();
	static void threadError(std::string errMsg);

	Vision();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void SetCOG(double mCOGX, double mCOGY);
	void SetTgtFlag(int mValidTgtFlag);
	void SetTgtAngles(double mtgtAngleX, double mtgtAngleY);
	void SetTgtDist(double mtgtDistance);
	void SetTgtTransCorrection(double madjTgtTransCorrection, double mtgtTransCorrection);
	void SetCurrYaw( double yaw);
	void SetAngleCorrection(double correction);
	void SetTipHdgDist(double hdg, double dist);
	void SetTipShiftData(double totDist, double hdg1, double hdg2, double fwdDist);
	void SetTipShiftAnlges(double angle1, double angle2);
	void SetActiveWheel(double a, double b);

	int GetValidTgtFlag();
	double GetTgtDist();
	double GetShiftHdg1();
	double GetShiftHdg2();
	double GetShiftFwdDist();
	double GetShiftDist();
	double GetShiftAngle1();
	double GetShiftAngle2();
	double GetActiveWheelA();
	double GetActiveWheelB();
	double GetTgtTransCorrection();
	double GetAdjTgtTransCorrection();
	double GetCOGX();
	double GetCOGY();
	double GetTgtAngleX();
	double GetTgtAngleY();
	double GetCurrYaw();
	double GetAngleCorrection();
	double GetTipHdg();
	double GetTipDist();

	double GetUDPCOGX();
	double GetUDPCOGY();

	void Update_Smartdashboard(double mode);

};

#endif
