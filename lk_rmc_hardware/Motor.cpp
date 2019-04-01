#include <lk_rmc_hardware/Motor.h>
// #include "include/Motor.h"

#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
// #include "ctre/Phoenix.h"

#include <string>

MotorInfo::MotorInfo(MotorType id)
{
	this->id = id;

	switch (id)
	{
	case BASE_FL:
		canId = 0;
		hasEncoder = true;
		name = "BASE_FL";
		break;

	case BASE_FR:
		canId = 1;
		hasEncoder = true;
		name = "BASE_FR";
		break;

	case BASE_BL:
		canId = 2;
		hasEncoder = true;
		name = "BASE_BL";
		break;

	case BASE_BR:
		canId = 3;
		hasEncoder = true;
		name = "BASE_BR";
		break;

	case DEPO:
		canId = 4;
		hasEncoder = true;
		name = "DEPO";
		break;

	case INTK_DRV:
		canId = 5;
		hasEncoder = false;
		name = "INTK_DRV";
		break;

	case INTK_LIFT_L:
		canId = -1; // stepper
		hasEncoder = false;
		name = "INTK_LIFT_L";
		break;

	case INTK_LIFT_R:
		canId = -1; // stepper
		hasEncoder = false;
		name = "INTK_LIFT_R";
		break;

	default:
		canId = -1;
		hasEncoder = false;
		name = "NULLMOTOR";
		id = NULLMOTOR;
		break;
	}
}

MotorInfo::~MotorInfo(void)
{
}

MotorInfo::MotorType MotorInfo::getType(void)
{
	return this->id;
}

int MotorInfo::getCanId(void)
{
	return this->canId;
}

std::string MotorInfo::typeToString(void)
{
	return this->name;
}

Motor::Motor(MotorInfo info) : info(info), motorcontrol::can::TalonSRX((int)info.getCanId())
{
	this->info = info;
}

Motor::~Motor(void)
{
}

MotorInfo Motor::getInfo(void)
{
	return this->info;
}
