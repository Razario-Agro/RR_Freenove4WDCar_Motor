/*
  RR_Freenove4WDCar_Motor.cpp - Library for Arduino Motor HC-SR04.
  Created by Roman Rainov, Janaury 29, 2024.
  Released into the private domain.
*/

#include "Arduino.h"
#include "RR_Freenove4WDCar_Motor.h"

RRFreenove4WDCarMotor::RRFreenove4WDCarMotor()
{
}

RRFreenove4WDCarMotor::RRFreenove4WDCarMotor(
	bool motorDirection,
	byte pinDirectionLeft,
	byte pinDirectionRight,
	byte pinMotorPwmLeft,
	byte pinMotorPwmRight)
{
	_motorDirection = motorDirection;
	_pinDirectionLeft = pinDirectionLeft;
	_pinDirectionRight = pinDirectionRight;
	_pinMotorPwmLeft = pinMotorPwmLeft;
	_pinMotorPwmRight = pinMotorPwmRight;
}

void RRFreenove4WDCarMotor::setup()
{
	pinMode(_pinDirectionLeft, OUTPUT);
	pinMode(_pinMotorPwmLeft, OUTPUT);
	pinMode(_pinDirectionRight, OUTPUT);
	pinMode(_pinMotorPwmRight, OUTPUT);
}

void RRFreenove4WDCarMotor::stop()
{
	analogWrite(_pinMotorPwmLeft, 0);
	analogWrite(_pinMotorPwmRight, 0);
}

void RRFreenove4WDCarMotor::forward(unsigned int speed)
{
	digitalWrite(_pinDirectionLeft, _motorDirection);
	digitalWrite(_pinDirectionRight, !_motorDirection);
	analogWrite(_pinMotorPwmLeft, getSpeed(speed));
	analogWrite(_pinMotorPwmRight, getSpeed(speed));
}

void RRFreenove4WDCarMotor::backward(unsigned int speed)
{
	digitalWrite(_pinDirectionLeft, !_motorDirection);
	digitalWrite(_pinDirectionRight, _motorDirection);
	analogWrite(_pinMotorPwmLeft, getSpeed(speed));
	analogWrite(_pinMotorPwmRight, getSpeed(speed));
}

void RRFreenove4WDCarMotor::rotateLeft(unsigned int speed)
{
	digitalWrite(_pinDirectionLeft, !_motorDirection);
	digitalWrite(_pinDirectionRight, !_motorDirection);
	analogWrite(_pinMotorPwmLeft, getSpeed(speed));
	analogWrite(_pinMotorPwmRight, getSpeed(speed));
}

void RRFreenove4WDCarMotor::rotateRight(unsigned int speed)
{
	digitalWrite(_pinDirectionLeft, _motorDirection);
	digitalWrite(_pinDirectionRight, _motorDirection);
	analogWrite(_pinMotorPwmLeft, getSpeed(speed));
	analogWrite(_pinMotorPwmRight, getSpeed(speed));
}

float RRFreenove4WDCarMotor::getSpeed(byte speed)
{
	float voltageOffset = getVoltageCompensation();
	float speedOffset = speed + voltageOffset;
	return speedOffset;
}

float RRFreenove4WDCarMotor::getVoltageCompensation()
{
	// The PWM value represents different speeds when the voltage of battery changes.
	// So we set a speedOffset to compensate the difference.
	float voltageOffset = MAX_VOLTAGE - _battery.getBatteryVoltage();
	return voltageOffset * 20; // 20 is tested value.
}