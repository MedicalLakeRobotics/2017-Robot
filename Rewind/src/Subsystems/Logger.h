// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef LOGGER_H
#define LOGGER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

/**
 *
 *
 * @author ExampleAuthor
 */
class Logger: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// ---- Logging variables ----
	std::string fileName;
	std::string base = "/home/lvuser/logs/robotLog";
	//std::string base = "/media/sda1/logs/robotLog";
	std::ofstream outFile;
	PowerDistributionPanel* pdp;

	std::string line;
	std::vector<std::string> lines;

	double time, lastTime, leftLastDist, rightLastDist, avgLastDist;

	double LogFlag;

	void createFile();
	void startTime();

public:
	enum Mode{
		TELE = 0,
		Auto = 1
	};
	Mode mode;
	Timer timer;

	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	double lastPotPos;

	Logger();
	void appendLog(std::string s, double d);
	void appendLog(std::string s);
	void appendLog(std::string type, std::string sys, std::string s );
	void logDrivetrain();
	void logGearHandler();
	void logJoyAxis(std::shared_ptr<frc::Joystick> joy);
	void setLogFlag(double flag);
	double getLogFlag();
	void reSetLogTime();

	void printLog();
	void clearLog();
	double Round(double value, int digits);
};

#endif
