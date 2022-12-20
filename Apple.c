/*
Created by: Arjun Mandair & Ishan Sahu
Created on: September 27, 2022
Last Modified: September 27, 2022
Version: 1.0

Description of Code: Instructs a LEGO EV3 to perform specified movements
using the motors, motor encoders, and touch sensor

*/


task main()
{
	//Initializing Variables
	const float DISTANCE_CONSTANT_CM = 360/(2*PI*2.75);
	int distanceCount = 0;
	
	//Initializing Motor Encoder
	nMotorEncoder(motorD) = 0;
	
	//Initializing Sensors
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	
	//Diplaying group number and initials
	displayString(5, "Group 72 AM IS");
	
	//Waiting for button to be pushed
	while(!getButtonPress(buttonEnter))
	{	}
	while(getButtonPress(buttonEnter))
	{	}
	
	//While sensor is not hitting a wall, slowly move forward
	motor[motorA]=motor[motorD] = 50;
	while(SensorValue[S1]!=1)
	{	}
	
	//Stops robot after hitting wall
	motor[motorA]=motor[motorD] = 0;
	distanceCount = nMotorEncoder(motorD);
	wait1Msec(2000);
	
	//Resetting Motor Encoder
	nMotorEncoder(motorA) = nMotorEncoder(motorD) = 0;
	
	//Moves robot back 20cm
	motor[motorA]=motor[motorD] = -50;
	while (nMotorEncoder(motorA) >= -20 * DISTANCE_CONSTANT_CM)
	{
	}
	
	//Stops robot for 2 seconds
	motor[motorA] = motor[motorD] = 0;
	wait1Msec(2000);
	
	//Moves robot back twice the original distance between the wall and the front of the robot
	motor[motorA] = motor[motorD] = -25;
	while (nMotorEncoder(motorD) >= (-2 * distanceCount))
	{
	}
	motor[motorA] = motor [motorD] = 0;
	
	//Displays this weeks codeword
	displayString(7, "Apple");
	wait1Msec(10000);
	
}
