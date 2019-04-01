#include <lk_rmc_hardware/lk_hardware.h>
#include <lk_rmc_hardware/Motor.h>

#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/motorcontrol/ControlMode.h"
// #include "ctre/Phoenix.h"

#include <stdexcept>
#include <string>
#include <iostream>

Robot::Robot(void) : motorReady{false}
{
	numMotors = 0;
	baseReady = false;
	depoReady = false;
	intakeReady = false;
}

// destructor clears dynamically allocated motors
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

// returns a pointer to the specified motor
Motor &Robot::getMotor(MotorInfo::MotorType id)
{
	if (motorReady[id])
		for (Motor *m : motors)
			if (m->getInfo().getType() == id)
				return *m;

	throw std::invalid_argument("Motor " + MotorInfo(id).typeToString() + " not found\n");
}

bool Robot::initMotor(MotorInfo::MotorType id)
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

// disables all motors, untested
void Robot::stopAllMotors(void)
{
	for (Motor *m : motors)
		m->Set(ctre::phoenix::motorcontrol::ControlMode::Disabled, 0.0);
}

void Robot::initBase(void)
{
	if (baseReady)
		return;

	for (int i = MotorInfo::BASE_FL; i <= MotorInfo::BASE_BR; i++)
		initMotor(static_cast<MotorInfo::MotorType>(i));

	baseReady = true;
}

void Robot::initDepo(void)
{
	if (depoReady)
		return;

	initMotor(MotorInfo::DEPO);
	depoReady = true;
}

void Robot::initIntake(void)
{
	if (intakeReady)
		return;

	for (int i = MotorInfo::INTK_DRV; i <= MotorInfo::INTK_LIFT_R; i++)
		initMotor(static_cast<MotorInfo::MotorType>(i));

	intakeReady = true;
}

// starts up CAN interface and returns error code
int32_t Robot::initCANInterface(void)
{
	int32_t error;
	// returns 0 if successfully initialized
	if (error = ctre::phoenix::platform::can::SetCANInterface("can0"))
		std::cout << "CAN Initialization returned error code: " << error << "\n";

	return error;
}
