/*
  RR_Freenove4WDCar_Motor.h - Library for Arduino Motor.
  Created by Roman Rainov, Janaury 29, 2024.
  Released into the private domain.
*/
#ifndef RR_Freenove4WDCar_Motor_h
#define RR_Freenove4WDCar_Motor_h

#include "Arduino.h"
#include "RR_Freenove4WDCar_Battery.h"

class RRFreenove4WDCarMotor
{
private:
	bool _motorDirection = true;
	byte _pinDirectionLeft = 4;
	byte _pinDirectionRight = 3;
	byte _pinMotorPwmLeft = 6;
	byte _pinMotorPwmRight = 5;

	RRFreenove4WDCarBattery _battery;

	float getVoltageCompensation();
	float getSpeed(byte speed);

public:
	const float MAX_VOLTAGE = 8.4;
	const float SPEED_OFFSET_PER_V = 35; //this is tested value.

	RRFreenove4WDCarMotor();
	RRFreenove4WDCarMotor(
		bool motorDirection,
		byte pinDirectionLeft,
		byte pinDirectionRight,
		byte pinMotorPwmLeft,
		byte _pinMotorPwmRight);
	void setup();
	void stop();
	void forward(unsigned int speed);
	void backward(unsigned int speed);
	void rotateLeft(unsigned int speed);
	void rotateRight(unsigned int speed);
};

#endif