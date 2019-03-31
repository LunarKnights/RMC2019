#include <lk_rmc_hardware/lk_hardware.h>
#include <lk_rmc_hardware/Motor.h>

#include "ctre/phoenix/platform/Platform.h"
// #include "ctre/Phoenix.h"

#include <stdexcept>
#include <string>
#include <iostream>

Robot::Robot(void)
{
	numMotors = 0;
	baseReady = false;
	depoReady = false;
	intakeReady = false;
	motorReady = {0};
}

Robot::~Robot(void)
{
	for (Motor *m : motors)
		delete m;
	motors.clear();
}

int Robot::getNumMotors(void)
{
	return numMotors;
}

Motor *Robot::getMotor(MotorType id)
{
	if (motorReady[id])
		for (auto i = motors.begin(); i != motors.end(); ++i)
			if (i->info.id == id)
				return *i;

	throw std::invalid_argument("Motor " + MotorInfo(id).typeToString() + " not found\n");
}

bool Robot::initMotor(MotorType id)
{
	if (!motorReady[id])
	{
		motors.push_back(new Motor(MotorInfo(id)));
		motorReady[id] = true;
		numMotors++;
		return true;
	}

	throw std::invalid_argument("Motor " + MotorInfo(id).typeToString() + " already set!\n");
}

// TODO: this
void Robot::stopAllMotors(void)
{
}

void Robot::initBase(void)
{
	if (baseReady)
		return;

	for (int i = BASE_FL; i <= BASE_BR; i++)
		initMotor(i);

	baseReady = true;
}

void Robot::initDepo(void)
{
	if (depoReady)
		return;

	initMotor(DEPO);
	depoReady = true;
}

void Robot::initIntake(void)
{
	if (intakeReady)
		return;

	for (int i = INTK_DRV; i <= INTK_LIFT_R; i++)
		initMotor(i);

	intakeReady = true;
}

int32_t Robot::initCANInterface(void)
{
	if (int32_t error = ctre::phoenix::platform::can::SetCANInterface("can0"))
		std::cout << "CAN Initialization returned error code: " << error << "\n";

	return error;
}
