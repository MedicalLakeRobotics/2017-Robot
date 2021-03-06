// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/DriveByJoystickCmd.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    frontLeftSpdCtr = RobotMap::drivetrainFrontLeftSpdCtr;
    frontRightSpdCtr = RobotMap::drivetrainFrontRightSpdCtr;
    rearLeftSpdCtr = RobotMap::drivetrainRearLeftSpdCtr;
    rearRightSpdCtr = RobotMap::drivetrainRearRightSpdCtr;
    robotDrive41 = RobotMap::drivetrainRobotDrive41;
    leftDriveEncoder = RobotMap::drivetrainLeftDriveEncoder;
    rightDriveEncoder = RobotMap::drivetrainRightDriveEncoder;
    irProxLeft = RobotMap::drivetrainIrProxLeft;
    irProxRight = RobotMap::drivetrainIrProxRight;
    sonar = RobotMap::drivetrainSonar;
    probeLmtSw = RobotMap::drivetrainProbeLmtSw;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	ahrs = new AHRS(SerialPort::kMXP);
	pdp = new PowerDistributionPanel();

    // ------- Initialize variables to zero ---------------------
    MotorLeft = MotorRight = MotorSpeed = MotorAngle = MotorMode = 0;
  	JoyXaxis = JoyYaxis = JoyTwist = JoyThrottle = JoyReverse=0;
   	throttle = yValue = twistValue = xValue = 0;

   	currHdg = beginHdg = endHdg = 0;
   	gyroLastHdg = gyroHdg = gyroDrift = origCorrection = correction = firstTimeFlag = 0;
   	proxValue = 0;

    left.dist = 	left.enc = 	left.lastDist = 	left.lastEnc = 	left.vel = 	0;
    right.dist = 	right.enc = right.lastDist = 	right.lastEnc = right.vel = 0;
    avg.dist = 		avg.enc = 	avg.lastDist = 		avg.lastEnc = 	avg.vel = 	0;
    zone = tgtDist = tgtRemainDist = 0;
    lastTime = 0;
    pidFirstFlag[0] = pidFirstFlag[1] = 0;

    // ---------- Startup timer for speed calculations -------
	timer.Reset();
	timer.Start();

   	gyroLastHdg = ahrs->GetYaw();
   	currHdg=0, beginHdg=0, endHdg=0;
   	robotDrive41->SetSafetyEnabled(false);	// possibly remove this line may not be needed
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveByJoystickCmd());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// ---------------------------------------------------------------------
// ----------------- Drive Motor Methods -------------------------------
void Drivetrain::StopMtrs()	{
	frontLeftSpdCtr->Set(0);
	frontRightSpdCtr->Set(0);
	rearLeftSpdCtr->Set(0);
	rearRightSpdCtr->Set(0);
	MotorLeft = MotorRight = MotorAngle = MotorSpeed = 0;
	MotorMode = 0;
	CalcDrivetrainSpeeds();		// we could still be coasting
	left.currPwr = right.currPwr = 0;
}

void Drivetrain::DriveByJoystick(std::shared_ptr<frc::Joystick> joy) {
	JoyXaxis = joy->GetX();
	JoyYaxis = joy->GetY();
	JoyTwist = joy->GetTwist();
	JoyThrottle = joy->GetThrottle();
	JoyReverse = 0;
	if (joy->GetRawButton(11) == true){
		JoyYaxis = JoyYaxis * -1;	// reverse direction
		JoyReverse = 1;
	}
	throttle=JoyThrottle;								// put throttle value into variable Throttle
	throttle=((throttle-1)/-2);							// converts range to 0 to +1
	yValue=JoyYaxis;									// sets y value of joystick to variable YValue

	if(((yValue) <= (XYDEADBAND * throttle)) &&
	   ((yValue) >= - (XYDEADBAND * throttle)))
			yValue=0;									// if YValue is within the deadband, don't move
	else
			yValue=yValue*throttle;

	if (joy->GetRawButton(2) == true){
			// we HAVE pressed for slower speed so go slower
			yValue = yValue * 0.5;
		}

	MotorSpeed = yValue*-1;
	twistValue = JoyTwist;								// sets twist value of joystick to variable TwistValue

	// ---- new twist deadband code TEST !! ------
	double twistOffset = 0.1;	// 10 percent deadband
	//double twistLimit = 0.5;	// second scall for twist to limit total speed
	double twistThrottle = throttle;
	double newTwistValue = twistValue;

	if(twistValue > 0){
		newTwistValue -= twistOffset;
		if (newTwistValue < 0) newTwistValue = 0; }
	else {
		newTwistValue += twistOffset;
		if (newTwistValue > 0) newTwistValue = 0; }
	newTwistValue *= (twistThrottle + (twistOffset / 2));
	//newTwistValue *= twistLimit;

	if (joy->GetRawButton(2) == true){
		// we have not pressed for faster rotation speed so go slower
		twistValue = (newTwistValue/TWISTTHROTTLEMOD) * 0.8;
	} else {
		// we have pressed for faster rotation speed
		twistValue = newTwistValue/TWISTTHROTTLEMOD;
	}



// --- this was the working code !
//	if((twistValue <= (TWISTDEADBAND * throttle)) &&
//	   (twistValue >= - (TWISTDEADBAND * throttle)))
//			twistValue=0;								// if YValue is within the deadband, don't move
//	else
//			twistValue=((twistValue*throttle)/TWISTTHROTTLEMOD);// changing TwistValue based on Throttle value

	MotorAngle = twistValue*-1;

	double driftComp = 0.2;
	if(MotorSpeed < 0) driftComp= -0.1;

	if(joy->GetRawButton(2) == true){
		robotDrive41->ArcadeDrive(MotorSpeed, MotorAngle);
	}
	else{
		robotDrive41->ArcadeDrive(MotorSpeed , MotorAngle+ driftComp);	// these are backward as needed for showbot ????????????
	}




	MotorLeft = MotorRight = 0;
	MotorMode = 1;
	CalcDrivetrainSpeeds();
	left.currPwr = right.currPwr = MotorSpeed;			// This is not real because of the twist angle mixing
}


void Drivetrain::Drive(float speed, float turn){		// Gyro assist straight Drive
	if(firstTimeFlag==0){
		gyroLastHdg=GetGyroHeading();
		firstTimeFlag=1;
	}
	CalculateCorrection(speed);
	MotorLeft = MotorRight = 0;
	MotorAngle = correction;
	MotorSpeed = speed;
	MotorMode = 2;
	robotDrive41->Drive(MotorSpeed, correction);
	CalcDrivetrainSpeeds();
	left.currPwr = right.currPwr = MotorSpeed;		// these might be off slightly by gyro correction
}

void Drivetrain::DriveToHdg(float speed, float hdg){
	if(firstTimeFlag==0){
		gyroLastHdg=hdg;
		firstTimeFlag=1;
	}
	CalculateCorrection(speed);
	MotorLeft = MotorRight = 0;
	MotorAngle = correction;
	MotorSpeed = speed;
	MotorMode = 2;
	robotDrive41->Drive(MotorSpeed, correction);
	CalcDrivetrainSpeeds();
	left.currPwr = right.currPwr = MotorSpeed;		// these might be off slightly by gyro correction
}

void Drivetrain::TankDrive(double leftspeed, double rightspeed) {	// Drive using left and right values
	robotDrive41->TankDrive(leftspeed,rightspeed);
	MotorLeft = leftspeed;
	MotorRight = rightspeed;
	MotorAngle = 0;
	MotorMode = 3;
	CalcDrivetrainSpeeds();
	left.currPwr = leftspeed;
	right.currPwr = rightspeed;
	MotorSpeed=0;
}


// ------------------------------------------------------------------------
// ------------------- Get Ultrasound Values ------------------------------
double Drivetrain::GetSonarVolt() 			{ return sonar->GetAverageVoltage(); }
double Drivetrain::GetSonarDistance()  		{ return (43.57739*sonar->GetAverageVoltage() - 2.04462); }


// ------------- IR Prox Methods ------------------------
double Drivetrain::GetLeftProx() 			{ return irProxLeft->GetAverageVoltage(); }		//return proxSensor->GetAverageVoltage();
double Drivetrain::GetRightProx() 			{ return irProxRight->GetVoltage(); }
double Drivetrain::GetLeftProxDistance()	{ return CalcProxDistance(irProxLeft->GetAverageVoltage());}
double Drivetrain::GetRightProxDistance()	{ return CalcProxDistance(irProxRight->GetAverageVoltage());}

double Drivetrain::CalcProxDistance(double x) {
	double x4 = -21.40373 * (x * x * x * x);
	double x3 =  92.07847 * ( x * x * x);
	double x2 = -115.84905 * (x * x);
	double x1 = 12.76574 *  x;
	double x0 = 55.153064;
	return (x4 + x3 + x2 + x1 + x0);
}
double Drivetrain::CalcProxAngle() {
	return 0;			// enter correct formula
}


// ------------------------------------------------------------------------
// ------------------------ Encoder Methods -------------------------------
void Drivetrain::InitEncoders(){
	leftDriveEncoder->SetDistancePerPulse( k_LeftEncConvConst);
	rightDriveEncoder->SetDistancePerPulse( k_RightEncConvConst);
}
void Drivetrain::ResetEncoders(){				// Set Encoders to zero
	leftDriveEncoder->Reset();
	rightDriveEncoder->Reset();
    left.dist = 	left.enc = 	left.lastDist = 	left.lastEnc = 	left.vel 	= 0;
    right.dist = 	right.enc = right.lastDist = 	right.lastEnc = right.vel 	= 0;
    avg.dist = 		avg.enc = 	avg.lastDist = 		avg.lastEnc = 	avg.vel 	= 0;
    lastTime = timer.Get();
}

int Drivetrain::GetLeftEncoder()  			{ return leftDriveEncoder->Get(); }
int Drivetrain::GetRightEncoder() 			{ return rightDriveEncoder->Get(); }
double Drivetrain::GetLeftEncoderDist() 	{ return (leftDriveEncoder->Get()  * k_LeftEncConvConst); }
double Drivetrain::GetRightEncoderDist() 	{ return (rightDriveEncoder->Get() * k_RightEncConvConst); }


// ------------------- Driver Statistics Methods -------------
// ------------- Speed and Distance Methods -----------------

double Drivetrain::GetRightSpeed()		{ return right.vel; }
double Drivetrain::GetLeftSpeed() 		{ return left.vel; }
int Drivetrain::GetLeftEnc()			{ return left.enc; }
int Drivetrain::GetRightEnc()			{ return right.enc; }
double Drivetrain::GetLeftDist() 		{ return left.dist; }
double Drivetrain::GetRightDist() 		{ return right.dist; }
double Drivetrain::GetAverageSpeed()	{ return avg.vel; }
double Drivetrain::GetAverageDist() 	{ return avg.dist; }
double Drivetrain::GetCorrection() 		{ return correction; }

void Drivetrain::CalcDrivetrainSpeeds(){
	double time = timer.Get();
	double deltaTime = time - lastTime;
	if (deltaTime == 0) deltaTime = 0.00000001;			// prevent divide by zero error
	lastTime = time;

	left.lastEnc = left.enc;
	left.enc = leftDriveEncoder->Get();

	left.lastDist = left.dist;
	left.dist = left.enc *  k_LeftEncConvConst;
	left.vel = (left.dist - left.lastDist) / deltaTime;

	right.lastEnc = right.enc;
	right.enc = rightDriveEncoder->Get();
	right.lastDist = right.dist;
	right.dist = right.enc  * k_RightEncConvConst;
	right.vel = (right.dist - right.lastDist) / deltaTime;

	avg.lastDist = avg.dist;
	avg.dist = (right.dist + left.dist) / 2;
	avg.vel = (right.vel + left.vel) / 2;

}

//double Drivetrain::CalcEncoderDist(double cnt){
//	return (cnt * k_EncoderConvConst);
//}

void Drivetrain::PutZoneData(int mzone, double mzoneSpeed, double mtgtDist, double mtgtRemainDist, double mtgtPwr) // Hold copy here for logging purposes
{
	zone = mzone;
	zoneSpeed = mzoneSpeed;
	tgtDist = mtgtDist;
	tgtRemainDist = mtgtRemainDist;
	tgtPwr = mtgtPwr;
}
double Drivetrain::GetZone() 			{ return zone; }
double Drivetrain::GetTgtDist() 		{ return tgtDist;}
double Drivetrain::GetTgtRemainDist() 	{ return tgtRemainDist;}
double Drivetrain::GetTgtPwr() 			{ return tgtPwr;}
double Drivetrain::GetZoneSpeed() 		{ return zoneSpeed; }


// -----------------------------------------------------------------------
// ----------------------------- Gyro Routines ---------------------------
void Drivetrain::GyroInit(){
	//gyro->SetDeadband( 0.015);						// may need to play with this value
	//gyro->SetSensitivity(0.007);						// used with analog gyro
}

void Drivetrain::ResetGyro() {
	ahrs->ZeroYaw();
}

double Drivetrain::GetGyroHeading()	{
	double hdg = ahrs->GetYaw();
	if (hdg < 0) hdg += 360;
	return hdg;
}

double Drivetrain::GetGyroYaw(){
	return ahrs->GetYaw();
}

void Drivetrain::SetFirstTimeFlag(int val)	{ firstTimeFlag = val;}

// ----------------- Limit switch Methods ----------------------------------------
bool Drivetrain::GetProbeLmtSw(){
	if (probeLmtSw->Get() == PRESSED) return true;
	return false;
}

// ----------------- Calculate Correction ----------------------------------------
void Drivetrain::CalculateCorrection(float speed){
	gyroHdg = GetGyroHeading();

	double angleOffset = gyroLastHdg - gyroHdg;
	if (angleOffset > 180) angleOffset -= 360;
	if (angleOffset < -180) angleOffset += 360;
	origCorrection = angleOffset * kGyroCorrectionConstant;				// this code uses the new navx gyro
	//origCorrection = ( - (gyroHdg-gyroLastHdg) * kGyroCorrectionConstant); // this code used the old analog gyro
	correction = origCorrection;
	// -- Test for exceeding limits --
	if (correction < 0){
		if (correction < kGyroCorrectionLwrLimit)  correction = kGyroCorrectionLwrLimit;
	}
	else
	{
		if (correction > kGyroCorrectionUpperLimit)  correction = kGyroCorrectionUpperLimit;
	}
	//if (speed < 0) correction = correction * -1;
}

// ------------------------------------------------------------------------
// ------------------------ Smart Dashboard Methods -----------------------
void Drivetrain::Update_Smartdashboard(double mode){

	SmartDashboard::PutNumber("Encoder Left Cnt", GetLeftEncoder());
	SmartDashboard::PutNumber("Encoder Left Dist", Round(left.dist,2));
	// SmartDashboard::PutNumber("Encoder Left Speed", Round(left.vel,2));

	SmartDashboard::PutNumber("Encoder Right Cnt 2", GetRightEncoder());
	SmartDashboard::PutNumber("Encoder Right Dist", Round(right.dist,2));
	// SmartDashboard::PutNumber("Encoder Right Speed", Round(right.vel,2));

	SmartDashboard::PutNumber("Drivetrain Average Distance", Round(avg.dist,2));
	SmartDashboard::PutNumber("Drivetrain Average Speed", Round(avg.vel,2));

	SmartDashboard::PutNumber("Gyro Angle", Round(ahrs->GetYaw(),2));

	SmartDashboard::PutNumber("IR Prox Left Volt", Round(GetLeftProx(),2));
	SmartDashboard::PutNumber("IR Prox Left Dist", Round(GetLeftProxDistance(),2));
	SmartDashboard::PutNumber("IR Prox Right Volt",	Round(GetRightProx(),2));
	SmartDashboard::PutNumber("IR Prox Right Dist",	Round(GetRightProxDistance(),2));

	SmartDashboard::PutNumber("Sonar Volt",	Round(GetSonarVolt(),2));
	SmartDashboard::PutNumber("Sonar Right Dist", Round(GetSonarDistance(),2));

	//SmartDashboard::PutNumber("Pwr FrLt", pdp->GetCurrent(12));
	//SmartDashboard::PutNumber("Pwr RdRt", pdp->GetCurrent(13));
	//SmartDashboard::PutNumber("Pwr RrLt", pdp->GetCurrent(14));
	//SmartDashboard::PutNumber("Pwr FrRt", pdp->GetCurrent(15));

	if (probeLmtSw->Get() == PRESSED)
		SmartDashboard::PutString("Probe LmtSw", "Pressed");
	else
		SmartDashboard::PutString("Probe LmtSw", "Not Pressed");

	// SmartDashboard::PutNumber("Joy X-Axis", JoyXaxis);
	// SmartDashboard::PutNumber("Joy Y-Axis", JoyYaxis);
	// SmartDashboard::PutNumber("Joy Throttle", JoyThrottle);
	// SmartDashboard::PutNumber("Joy Twist", JoyTwist);
	// SmartDashboard::PutNumber("Joy Reverse", JoyReverse);
}

// ------------------------------------------------------------------------
// ----------------------------- Misc Methods -----------------------------
double Drivetrain::Round(double value, int digits){
	int mult = 1;
	if (digits == 0) mult = 1;
	else if (digits == 1) mult = 10;
	else if (digits == 2) mult = 100;
	else if (digits == 3) mult = 1000;
	else if (digits == 4) mult = 10000;
	else if (digits == 5) mult = 100000;
	else if (digits == 6) mult = 1000000;
	return (round(value * mult) / mult);
}


// ------------------------------------------------------------------------
// ------------------------ PID Methods -----------------------------------
void Drivetrain::PIDreset(int motor){
	// motor 0=left, 1=right motor states
	iAccum[motor] = dErr[motor] = pidOut[motor] = prevErr[motor] = pidFirstFlag[motor] = 0;
}


void  Drivetrain::PIDSetConst(double p, double i, double d, double f){
	kpidP = p;
	kpidI = i;
	kpidD = d;
	kpidF = f;
}

void Drivetrain::PIDSetLimits(double max, double min, double izone, double ramp){
	kpidmax = max;
	kpidmin = min;
	kpidizone = izone;
	kpidramp = ramp;
}

void Drivetrain::PIDSetPoint(double tgtVel, int motor){
}


double Drivetrain::PIDCalcValue(double currVel, double tgtVel, int motor){
	double err, absErr;
	err = tgtVel - currVel;
	pidErr = err;
	absErr = err;
	if (err < 0) absErr = -absErr;

	// ----- Integrate error----------
	if (pidFirstFlag[motor] == 0){  // first time through clear integrate error
		iAccum[motor] = 0;
		pidOut[motor] = kpidramp; }	// save the current ramp  ?????????????
	else if (( !kpidizone ) || ( absErr < kpidizone)){
		iAccum[motor] += err; }		// izone is not used or abserr is within izone
	else {
		iAccum[motor] = 0;	}

	if (pidFirstFlag[motor] != 0)	// first time through clear integrate error
		dErr[motor] = (err - prevErr[motor]);
	else
		dErr[motor] = 0;

	// ------------------------------------------
	// P gain x distance away from where we want ---
	pidOutBeforeRamp = err * kpidP;

	if (iAccum[motor] && kpidI){
		// our accumulated error times I gain, if you want the robot to creep up then pass non zero I gain
		pidPgain = iAccum[motor] * kpidI;
		pidOutBeforeRamp += iAccum[motor] * kpidI;
	}

	// -------------------------------------------
	// Derivative gain, if you want to react to sharp changes in error (smooth things out)
	pidDgain = dErr[motor] * kpidD;
	pidOutBeforeRamp += dErr[motor] * kpidD;

	// feedforward on the set point
	pidFgain = dErr[motor] * kpidD;
	pidOutBeforeRamp += tgtVel * kpidF;

	// --------------------------
	// --- arm for next pass ----
	prevErr[motor] = err;
	pidFirstFlag[motor] = 1;		// we have now been through once

	// --------------------------
	// Honor ramprate limits
	if (kpidramp != 0){
		if (pidOutBeforeRamp >= pidOut[motor]){
			double deltaUp = pidOutBeforeRamp - pidOut[motor];
			if (deltaUp > kpidramp)
				deltaUp = kpidramp;
			pidOut[motor] += deltaUp;
		} else{
			double deltaDn = pidOut[motor] - pidOutBeforeRamp;
			if (deltaDn > kpidramp)
				deltaDn = kpidramp;
			pidOut[motor] -= deltaDn;
		}
	}else {
		pidOut[motor] = pidOutBeforeRamp;
	}

	std::cout << "PID Calc TgtSpeed=" + std::to_string(tgtVel) + " CurrSp=" + std::to_string(tgtVel);
	std::cout << " Err=" + std::to_string(err);
	std::cout << " FF=" + std::to_string(pidFirstFlag[motor]);
	std::cout << " PrevErr=" + std::to_string(prevErr[motor]);
	std::cout << " GainP=" + std::to_string(pidPgain);
	std::cout << " GainI=" + std::to_string(pidIgain);
	std::cout << " iAccum=" + std::to_string(iAccum[motor]);
	std::cout << " GainD=" + std::to_string(pidDgain);
	std::cout << " GainF=" + std::to_string(pidFgain);
	std::cout << " POBR=" + std::to_string(pidOutBeforeRamp);
	std::cout << " OUT=" + std::to_string(pidOut[motor]);
	std::cout << std::endl;
	return pidOut[motor];
}


