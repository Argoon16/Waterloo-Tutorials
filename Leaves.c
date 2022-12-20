/*
Created by: Arjun Mandair and Timothy Tsui
Created on: October 6, 2022
Last Modified: October 4, 2022
Version: 1.0

Purpose: Intructs a LEGO EV3 to perform specified movements using motors,
a color sensor, and a gyro sensor, as well as measure the length of a
red paper using motorencoders and an ultrasonic sensor
*/

//Function that sets the power of the motors to move the robot
void motorPowerSet(int motorPower1, int motorPower2)
{
	motor[motorA] = motorPower1;
	motor[motorD] = motorPower2;
}

/*
Function that calculates the length of a red paper using an
ultrasonic sensor
*/
float measureRedPaperForward(int sensorColor)
{
	float initialSensorValue = 0;
	float finalSensorValue = 0;
	while(SensorValue[S2] != (int)colorRed)
	{}
	initialSensorValue = SensorValue[S3];
	while(SensorValue[S2] == (int)colorRed)
	{}
	finalSensorValue = SensorValue[S3];
	return initialSensorValue - finalSensorValue;
}

/*
Function that calculates the length of a red paper using a
gyro sensor
*/
float measureRedPaperBackward(int sensorColor)
{
	float redPaperDistanceCm = 0;
	float const DISTANCE_CONSTANT_CM = (2*PI*2.75)/360;
	while(SensorValue[S2] != (int)colorRed)
	{}
	nMotorEncoder[motorA] = 0;
	while(SensorValue[S2] == (int)colorRed)
	{}
	redPaperDistanceCm = abs(nMotorEncoder[motorA])*DISTANCE_CONSTANT_CM;
	return redPaperDistanceCm;
}

task main()
{
	//Initializing Variables
	float paperDistance = 0;

	//Initializing Sensors and Motors
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Ultrasonic;
	wait1Msec(50);
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);

	//Diplaying Group Number and Initials
	displayString(3, "Group 73 AM TT");

	//Waiting for button to be pressed and released
	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}

	//Resetiing Motor Encoder
	nMotorEncoder[motorD] = 0;

	//Moving Robot Forward 40% Power
	motorPowerSet(40, 40);


	//Displaying Length of red paper using ultrasonic on Line 5
	paperDistance = measureRedPaperForward((int)colorRed);

	displayString(5, "%f", paperDistance);

	//Waiting for Robot to hit a wall
	while(SensorValue[S1] != 1)
	{}

	//Stopping Robot and then moving robot backwards
	motorPowerSet(0, 0);
	wait1Msec(500);
	motorPowerSet(-40, -40);

	//Measures and Displays Distance using MotorEncoder on Line 7
	paperDistance = measureRedPaperBackward((int)colorRed);
	displayString(7, "%f", paperDistance);

	//Driving Backwards to Original Location
	while(nMotorEncoder[motorD] > 0)
	{}
	motorPowerSet(0, 0);
	wait1Msec(2000);

	//Turning Robot 360 Degrees Counter Clockwise
	motorPowerSet(30, -30);
	while(getGyroDegrees(S4) > -360)
	{}
	motorPowerSet(0, 0);

	//Displaying Codeword on Line 10
	displayString(10, "Leaves");
	wait1Msec(10000);
}
