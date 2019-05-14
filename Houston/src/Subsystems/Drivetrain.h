// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "AHRS.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<SpeedController> frontLeftSpdCtr;
	std::shared_ptr<SpeedController> frontRightSpdCtr;
	std::shared_ptr<SpeedController> rearLeftSpdCtr;
	std::shared_ptr<SpeedController> rearRightSpdCtr;
	std::shared_ptr<RobotDrive> robotDrive41;
	std::shared_ptr<Encoder> leftDriveEncoder;
	std::shared_ptr<Encoder> rightDriveEncoder;
	std::shared_ptr<AnalogInput> irProxLeft;
	std::shared_ptr<AnalogInput> irProxRight;
	std::shared_ptr<AnalogInput> sonar;
	std::shared_ptr<DigitalInput> probeLmtSw;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	AHRS* ahrs;
	PowerDistributionPanel* pdp;

	//double 		k_EncoderConvConst = 0.064271;			// Distance per pulse in inches for show bot drivetrain
	//double 		k_EncoderConvConst = 0.035;				// Distance per pulse in inches for show 2017 bot (0.03499933713)

	double k_LeftEncConvConst = 0.0354062;
	double k_RightEncConvConst = 0.05084746;

	const float kEncoderConvPtTurn = 0.02978;			// avg degrees rotation per encoder cnt. Average lf & rt together

	const float TWISTTHROTTLEMOD=1.25;					//reserves memory for variable/attribute TWISTTHROTTLEMOD which is a constant
	const float XYDEADBAND=0.1;							//reserves memory for variable/attribute XYDEADBAND which is a constant
	float 		TWISTDEADBAND=0.025;					//reserves memory for variable/attribute TWISTDEADBAND which is a constant
	float throttle, yValue, twistValue, xValue;			// joystick working variable

	const float kMaxSonarConv = 22.0;					// Constant for Inches per volt value
	const float kProxSensorConv = 1.0;					// Conversion for inches per volt
	float proxValue;									// variable used in calculating distance

	const bool PRESSED = true;
	const bool NOTPRESSED = false;


	// These gyro correction values may need to be tweaked based on floor type, Speed, Direction ???
	//float kGyroCorrectionConstant = 0.018;				// 0.018 seemd good maybe lower than idel??

	float kGyroCorrectionConstant = 0.021;				// 0.018 seemd good maybe lower than idel??
	float kGyroCorrectionLwrLimit = -0.090;				// -0.035 wasnt experienced at 0.005 correction
	float kGyroCorrectionUpperLimit = 0.090;
	//float kGyroCorrectionLwrLimit = -0.070;				// -0.035 wasnt experienced at 0.005 correction
	//float kGyroCorrectionUpperLimit = 0.070;

	float gyroLastHdg, gyroHdg, gyroDrift, origCorrection, correction;
	float gyroXraw,gyroYraw,gyroZraw;
	int firstTimeFlag;
	float tgtHdg, lastTgtHdg;

public:
	Drivetrain();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	// --------------- Public Variables -----------------------------------------

	float currHdg, beginHdg, endHdg;

	double MotorLeft;			// tank drive
	double MotorRight;			// tank drive
	double MotorSpeed;			// arcade drive
	double MotorAngle;			// arcade drive
	double MotorMode;			// arcade = 0, tank = 1

	double JoyXaxis;
	double JoyYaxis;
	double JoyTwist;
	double JoyThrottle;
	double JoyReverse;

	// ---------------- State variables -------------
	typedef struct Driver{
		double enc;
		double lastEnc;
		double dist;
		double lastDist;
		double vel;
		double currPwr;
	} Driver;

	Driver left,right,avg;
	int zone;				// 0=no motion in process, 1=A zone (last), 2=B Zone, 3=C zone, 4=D zone, 5=E Zone
	double tgtDist, tgtRemainDist, tgtPwr, zoneSpeed;



	// ------------ Pid Variables --------------
	double kpidP, kpidI, kpidD, kpidF;
	double kpidmax, kpidmin, kpidizone, kpidramp;
	double pidDgain, pidIgain, pidPgain, pidFgain;
	//double pidOutLmt, pidDeltaUp, pidDeltaDn, pidRampRate, BDC_GetThroat;
	double pidErr, pidOutBeforeRamp, iAccum[2], dErr[2], pidOut[2], prevErr[2], pidFirstFlag[2];		// 0=left, 1=right motor states

	// ----------------------------------------------
	// --- variables to calculate speed from encoders
	Timer timer;
	double lastTime;

	// ----------- Drive Methods -------------------
	void StopMtrs();							// Stop all Motors
	void TankDrive(double leftspeed, double rightspeed);	// Drive using left and right values
	void DriveByJoystick(std::shared_ptr<frc::Joystick> joy);
	float GetHeading(int method);				// return  heading in degrees. 0=gyro, 1=encoder method
	void Drive(float speed, float turn);
	void DriveToHdg(float speed, float hdg);

	// --------------- PID Methods ------------------
	void  PIDSetConst(double p, double i, double d, double f);
	void PIDSetLimits(double max, double min, double izone, double ramp);
	void PIDSetPoint(double tgtVel, int motor);
	double PIDCalcValue(double currVel, double tgtVel, int motor);
	void   PIDreset(int motor);

	// ----------- Ultrasound Methods -------------------
	double GetSonarVolt();
	double GetSonarDistance();

	// ------------- IR Prox Methods ------------------------
	double GetLeftProx();
	double GetRightProx();
	double GetLeftProxDistance();
	double GetRightProxDistance();
	double CalcProxDistance(double volt);
	double CalcProxAngle();

	// ------------------- Encoder Methods --------------------
	void InitEncoders();
	void ResetEncoders();						// Set Encoders to zero
	int GetLeftEncoder();						// Get Left Encoder Value
	int GetRightEncoder();						// Get Right Encoder Value

	void CalcDrivetrainSpeeds();
	double GetLeftSpeed();
	double GetRightSpeed();
	int GetLeftEnc();
	int GetRightEnc();
	double GetLeftDist();
	double GetRightDist();
	double GetAverageSpeed();
	double GetAverageDist();

	// ------------------- Driver Statistics Methods -------------

	//double CalcEncoderDist(double cnt);
	double GetLeftEncoderDist();
	double GetRightEncoderDist();
	double GetRightEncoderSpeed();
	double GetLeftEncoderSpeed();
	void PutZoneData(int zone, double zoneSpeed, double tgtDist, double tgtRemainDist, double tgtPwr);
	double GetZone();
	double GetTgtDist();
	double GetTgtRemainDist();
	double GetTgtPwr();
	double GetZoneSpeed();
	double GetCorrection();


	// ----------------- Gyro Methods ------------------------
	void GyroInit();
	void ResetGyro();							// Set Gyroscope to zero
	double GetGyroHeading();					// Get Gyroscope value
	double GetGyroYaw();
	void SetFirstTimeFlag(int val);				// Set or clear the first time flag for gyro correction
	void CalculateCorrection(float speed);					// Print gyroscope values
	double GetDistance();						// return The distance driven (average of lf and rt encoders).

	// ---------------- Limit Switch Methods ---------------
	bool GetProbeLmtSw();

	// ------------------- Misc Methods ------------------------
	void Update_Smartdashboard(double mode);

	void ZeroBeginEndValues();
	void PostBeginValues();
	void PostEndValues();
	void PostCurrValues();
	void DisplaySmartdashValues();
	void DisplaySmartdashSimple();
	double Round(double value, int digits);
	/*
	float GetDistanceBySonar();
	float GetSonarValue();
	float GetDistanceByProx();
	float GetProxValue();
	 */
};

#endif
