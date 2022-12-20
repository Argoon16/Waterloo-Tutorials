/*
Created by: Arjun Mandair and Aakifa Akhtar
Created on: October 25, 2022
Last modified: October 25, 2022
Version: 1.0

Purpose: To make a Lego EV3 robot drive continuously in a square until
either the touch sensor is touched, in which it will turn and drive
continuously along the same square the other way, or the enter button
is touched, where the robot stops completely.

Assumptions: The touch sensor is only touched once per side (one object
per side)
*/

//Configures all sensors to standard configuration
void configureAllSensors();

//Powers both drive motors with the same power
void drive(int motor_power);

//Powers both motors independently
void driveBoth (int motor_power_A, int motor_power_D);

//Wait for push and release of specified button
void waitButton(TEV3Buttons button_name);

/*
Improvements made on the rotateRobot function: We decreased the
turning speed of the robot to improve the accuracy of the gyro
sensor, allowing the robot to stay on the same square path
with more accuracy
*/

/*
Rotates robot in place to given angle. Positive angles are clockwise
when viewed from above
*/
int rotateRobot(int angle, int cw)
{
	resetGyro(S4);

	if (angle>0)
	{
		driveBoth(-10,10);
	}
	else
	{
		driveBoth(10,-10);
	}

	while (abs(getGyroDegrees(S4))<abs(angle))
	{
		if(getButtonPress(buttonEnter)) //Checking if enter button is pressed
		{
			return 2;
		}
	}
	return cw;
}

/*
Improvements made on the driveDistance function: We decreased
the speed of the robot to improve the accuracy of where the
robot will stop, allowing the robot to stay on the same square path
*/

//Drives robot straight forward for a given distance
int driveDistance(int distance, int cw)
{
	nMotorEncoder[motorA]=0;
	const float CM_TO_DEG = 180/(2.75*PI);

	drive(40);

	while (abs(nMotorEncoder[motorA])<abs(distance*CM_TO_DEG))
	{
		if(getButtonPress(buttonEnter)) //Checking if enter button is pressed
		{
			return 2;
		}

		if(SensorValue(S1)!=0) //Checking if touch sensor is pressed
		{
			int distanceback = 0;
			distanceback = nMotorEncoder[motorA];
			cw = rotateRobot(180, cw);
			nMotorEncoder[motorD] = 0;
			drive(40);
			while(abs(nMotorEncoder[motorD])<distanceback)
			{}
			if (cw == 1)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	return cw;
}

task main()
{
	//Initializing Variables
	int cw = 1;
	configureAllSensors();
	waitButton(buttonEnter);

	//Continuing while loop until enter button is pressed
	while(cw!=2)
	{
		cw = driveDistance(50, cw);
		if(cw == 1)
		{
			cw = rotateRobot(90, cw);
		}
		else if(cw == 0)
		{
			cw = rotateRobot(-90, cw);
		}
		else
		{
			drive(0);
		}
	}
}

//Function that configures all sensors
void configureAllSensors()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}

//Powers both drive motors with the same power
void drive(int motor_power)
{
	motor[motorA] = motor[motorD] = motor_power;
}

//Powers both motors independently
void driveBoth(int motor_power_A, int motor_power_D)
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
}

//Function that waits for push and release of specified button
void waitButton(TEV3Buttons button_name)
{
	while(!getButtonPress(button_name))
	{}
	while(getButtonPress(button_name))
	{}
}
